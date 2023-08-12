#include "system_control.h"

#include "login.h"

// 系统控制变量初始化
void sysctl_init(SystemCtl *sysctl)
{
    sysctl->bLogin = false;
    sysctl->accountInfoFilename = "./lhy/account_info";

    init_account_list(sysctl->accountInfoFilename, &sysctl->accountList);
}

void sysctl_login(SystemCtl *sysctl)
{
    login(sysctl);
}

void sysctl_deinit(SystemCtl *sysctl)
{
    destroy_account_list(&sysctl->accountList);
}
