
#ifndef _RE_ACCOUNT_INFO_H_
#define _RE_ACCOUNT_INFO_H_

#include <stdio.h>
#include <stdbool.h>//使用布尔类型
#define  MAX_ACCOUNT_STRLEN 12

/*枚举  账户类型集合*/
typedef enum
{
    Ksuper=0,
    Kuser,
}AccountType;

/*账号信息结构*/
typedef struct 
{
    int id;
    char name[ MAX_ACCOUNT_STRLEN+1];
    char pwd[ MAX_ACCOUNT_STRLEN+1];
    AccountType type;
}AccountInfo;

/*账号列表结构*/
typedef struct 
{
    AccountInfo *info;
    int num; 
}AccountList;

AccountInfo account_warp(const char *name,const char *pwd);
bool creat_accountlist(AccountList *list,FILE *fp);
void init_account_info(char *filename,AccountList *list);
bool find_account_list(const AccountList *list,const AccountInfo *acc);


#endif
