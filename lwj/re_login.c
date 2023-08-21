#include "re_login.h"
#include "re_utils.h"
#include "re_system_control.h"


bool login(SystemCtl *systemctl)
{
    char name[MAX_ACCOUNT_STRLEN + 1];
    char pwd[MAX_ACCOUNT_STRLEN + 1];

    LOG("\ninput your name :");
    scanf("%s",&name);
    LOG("\ninput your pwd :");
    scanf("%s",&pwd);

    AccountInfo account = account_warp(name,pwd);
    if(find_account_list(&systemctl->list,&account))
    {
        systemctl->blogin = true;
        systemctl->login_info=account;
        LOG("\n-----------登陆成功-----------\n");
        return true;
    }
    return false;
}

