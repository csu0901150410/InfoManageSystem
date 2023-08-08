#ifndef _ACCOUNT_INFO_H_
#define _ACCOUNT_INFO_H_

#include "stdio.h"

// 账号类型枚举
typedef enum
{
    kGuest = 0,
    kAdmin,
    kNormal,
} AccountType;

// 账号信息
typedef struct
{
    int id;// 账号id
    char account[12];// 账号名
    char pwd[12];// 账户密码
    AccountType type;// 账户类型
} AccountInfo;

// 账号信息管理器
typedef struct
{
    FILE *fp;
} AccountController;

void test_info();
void open_account_info();

#endif // _ACCOUNT_INFO_H_
