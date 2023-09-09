#ifndef _LHY_SHELL_H_
#define _LHY_SHELL_H_

/**
 * @brief Reference :
 * 1、https://brennan.io/2015/01/16/write-a-shell-in-c/
 * 2、https://en.cppreference.com/w/c
 * 
 */

// 接口函数的函数指针别名
typedef void (*interface_func)(void);
typedef char ** ShellArgs;

typedef ShellArgs (*retShellArgs)(void);
typedef int (*retInt)(void);

// Shell接口
typedef struct
{
    interface_func read_line;// shell读入一行
    interface_func destroy;// shell销毁一行，必须和read_line同时使用

    retShellArgs get_args;// shell获取解析的参数
    retInt get_args_nums;// shell获取参数数量

    ShellArgs args;
    int argNums;
} Shell;

void shell_init(Shell *shell);

#endif // _LHY_SHELL_H_