#include <string.h>

#include "system_control.h"

#include "login.h"
#include "utils.h"

// 系统控制变量初始化
void sysctl_init(SystemCtl *sysctl)
{
    sysctl->bLogin = false;
    sysctl->accountInfoFilename = "./lhy/account_info";
    sysctl->cmdEvent = kNone;

    init_account_list(sysctl->accountInfoFilename, &sysctl->accountList);
}

bool sysctl_login(SystemCtl *sysctl)
{
    if (sysctl->bLogin)
        return true;

    bool bLogin = login(sysctl);
    if (bLogin)
        LOGN("username>");
    return bLogin;
}

void sysctl_deinit(SystemCtl *sysctl)
{
    destroy_account_list(&sysctl->accountList);
}

void sysctl_cmd_parse(SystemCtl *sysctl)
{
    char cmd[MAX_CMD_STRLEN] = {0};
    gets(cmd);

    if (0 == strlen(cmd))
    {
        if (kNone == sysctl->cmdEvent)
            sysctl->cmdEvent = kEnter;
    }
    else
    {
        LOG("Input : %s", cmd);
    }
}

void sysctl_handle_event(SystemCtl *sysctl)
{
    if (kNone == sysctl->cmdEvent)
        return;

    switch (sysctl->cmdEvent)
    {
    case kEnter:
        LOGN("username>");
        break;
    
    default:
        break;
    }
}

void sysctl_polling(SystemCtl *sysctl)
{
    while (1)
    {
        if (!sysctl_login(sysctl))
            continue;

        sysctl_cmd_parse(sysctl);

        sysctl_handle_event(sysctl);
    }
}
