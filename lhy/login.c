#include "login.h"

#include "utils.h"

/**
 * @brief 登录函数
 * 
 * @param sysctl 系统变量指针
 * @return true 登录成功
 * @return false 登录失败
 */
bool login(SystemCtl *sysctl)
{
    char name[MAX_ACCOUNT_STRLEN + 1];// 账号名
    char pwd[MAX_ACCOUNT_STRLEN + 1];// 账户密码

    LOGN("\ninput your name : ");
    gets(name);
    LOGN("input your pwd  : ");
    gets(pwd);

    AccountInfo account = account_wrap(name, pwd);
    if (find_account_list(&sysctl->accountList, &account))
    {
        sysctl->bLogin = true;
        sysctl->account = account;
        return true;
    }
    return false;
}
