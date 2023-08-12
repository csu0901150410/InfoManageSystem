#ifndef _ACCOUNT_INFO_H_
#define _ACCOUNT_INFO_H_

#include <stdio.h>
#include <stdbool.h>

#define MAX_ACCOUNT_STRLEN  12

// 账号类型枚举
typedef enum
{
    kSuper = 0,
    kAdmin,
    kNormal,
    kGuest,
} AccountType;

// 账号信息
typedef struct
{
    int id;// 账号id
    char name[MAX_ACCOUNT_STRLEN + 1];// 账号名
    char pwd[MAX_ACCOUNT_STRLEN + 1];// 账户密码
    AccountType type;// 账户类型
} AccountInfo;

// 堆内存中的账号列表----也可以用链表来做
typedef struct
{
    AccountInfo *ptr;
    size_t num;
} AccountList;

// 账号信息管理器
typedef struct
{
    FILE *fp;
} AccountController;

void test_info();

bool create_account_list(AccountList *al, FILE *fp);
void destroy_account_list(AccountList *al);
void print_account_list(AccountList *al);
void init_account_list(char *filename, AccountList *al);
bool find_account_list(const AccountList *al, const AccountInfo *ai);
AccountInfo account_wrap(const char *name, const char *pwd);

#endif // _ACCOUNT_INFO_H_
