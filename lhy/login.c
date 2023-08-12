#include "login.h"

#include "utils.h"

void login(SystemCtl *sysctl)
{
    while (1)
    {
        char name[MAX_ACCOUNT_STRLEN + 1];// 账号名
        char pwd[MAX_ACCOUNT_STRLEN + 1];// 账户密码
        LOGN("\ninput your name : ");
        scanf("%s", name);
        LOGN("input your pwd : ");
        scanf("%s", pwd);

        AccountInfo account = account_wrap(name, pwd);
        if (find_account_list(&sysctl->accountList, &account))
        {
            sysctl->bLogin = true;
            LOGN("Login success\n");
            break;
        }
    }
}
