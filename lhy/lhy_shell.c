
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lhy_shell.h"

#define LSH_RL_BUFSIZE  1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM   " \t\r\n\a"

// 被隐藏的shell具体实现的结构体
typedef struct
{
    char *line;
    char **args;
} ShellImpl;

// 唯一的shell，不管外边创建了多少个Shell结构体变量，这里的ShellImpl结构体变量始终只有一个
static ShellImpl shellImpl;

// 具体实现

/**
 * @brief 读取命令行的输入
 * 
 * @return char* 返回读取到的字符串指针，该指针由调用者释放
 */
char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int index = 0;
    char *line = malloc(sizeof(char) * bufsize);
    int c;

    if (!line)
    {
        fprintf(stderr, "lsh: allocation failed\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();
        if (EOF == c || '\n' == c)
        {
            line[index] = '\0';
            return line;
        }
        else
            line[index] = c;
        index++;

        // 字符数超出则扩容
        if (index >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            line = realloc(line, bufsize);
            if (!line)
            {
                fprintf(stderr, "lsh: allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * @brief 将命令行字串 \p line 按照分隔符列表分割为若干子串
 * 
 * @param line 命令行字串
 * @return char** 子串数组
 */
char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE;
    int index = 0;
    char **tokens = malloc(bufsize * sizeof(char *));// 存放分割后字串指针的数组
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // 按照分隔符列表LSH_TOK_DELIM对line进行分割，将line中第一个匹配的分隔符变为'\0'，返回line
    // 将strtok内部静态指针指向第一个匹配的分隔符的下一个字符
    token = strtok(line, LSH_TOK_DELIM);
    while (NULL != token)
    {
        tokens[index] = token;
        index++;

        if (index >= bufsize)
        {
            // 扩容
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }

        // 传参为NULL，则从内部静态指针开始匹配分隔符列表，继续分割
        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[index] = NULL;// 子串数组以NULL结尾
    return tokens;
}

// 获取shell单例
ShellImpl *shell_get_instance(void)
{
    return &shellImpl;
}

// 接口桥接实现

void shell_read_line(void)
{
    ShellImpl *shell = shell_get_instance();
    if (shell->line)
    {
        free(shell->line);
        free(shell->args);
        shell->line = NULL;
        shell->args = NULL;
    }
    shell->line = lsh_read_line();
    shell->args = lsh_split_line(shell->line);
}

void shell_destroy(void)
{
    ShellImpl *shell = shell_get_instance();
    if (shell->line)
    {
        free(shell->line);
        shell->line = NULL;
    }

    if (shell->args)
    {
        free(shell->args);
        shell->args = NULL;
    } 
}

char **shell_get_args(void)
{
    ShellImpl *shell = shell_get_instance();
    return shell->args;
}

int shell_get_args_num(void)
{
    int count = 0;
    while (1)
    {
        char *arg = shell_get_instance()->args[count];
        if (NULL == arg)
            break;
        count++;
    }
    return count;
}

void shell_init(Shell *shell)
{
    // 绑定接口和实现
    shell->read_line = shell_read_line;
    shell->destroy = shell_destroy;

    shell->get_args = shell_get_args;
    shell->get_args_nums = shell_get_args_num;
}
