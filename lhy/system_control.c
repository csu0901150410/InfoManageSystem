#include <string.h>
#include <stdlib.h>

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

void sysctl_get_curr_user_name(SystemCtl *sysctl, char *name)
{
    strncpy(name, sysctl->account.name, MAX_ACCOUNT_STRLEN);
}

void sysctl_show_curr_user_name(SystemCtl *sysctl)
{
    LOGN("%s>", sysctl->account.name);
}

bool sysctl_login(SystemCtl *sysctl)
{
    if (sysctl->bLogin)
        return true;

    bool bLogin = login(sysctl);
    if (bLogin)
        sysctl_show_curr_user_name(sysctl);
    return bLogin;
}

bool sysctl_logout(SystemCtl *sysctl)
{
    if (!sysctl->bLogin)
        return true;

    sysctl->bLogin = false;
    return true;
}

void sysctl_deinit(SystemCtl *sysctl)
{
    destroy_account_list(&sysctl->accountList);
}

void sysctl_cmd_parse(SystemCtl *sysctl)
{
    if (kNone != sysctl->cmdEvent)
        return;

    char cmd[MAX_CMD_STRLEN] = {0};
    gets(cmd);

    if (0 == strlen(cmd))
        sysctl->cmdEvent = kEnter;
    else if (0 == strncmp("cls", cmd, MAX_CMD_STRLEN))
        sysctl->cmdEvent = kCls;
    else if (0 == strncmp("exit", cmd, MAX_CMD_STRLEN))
        sysctl->cmdEvent = kExit;
    else if (0 == strncmp("quit", cmd, MAX_CMD_STRLEN))
        sysctl->cmdEvent = kQuit;
    else
        sysctl->cmdEvent = kInvalid;
}

void sysctl_event_reset(SystemCtl *sysctl)
{
    sysctl->cmdEvent = kNone;
}

void sysctl_handle_event(SystemCtl *sysctl)
{
    if (kNone == sysctl->cmdEvent)
        return;

    switch (sysctl->cmdEvent)
    {
    case kEnter:
        sysctl_show_curr_user_name(sysctl);
        sysctl_event_reset(sysctl);
        break;

    case kCls:
        system("cls");
        sysctl_show_curr_user_name(sysctl);
        sysctl_event_reset(sysctl);
        break;

    case kExit:
        system("cls");
        sysctl_logout(sysctl);
        sysctl_event_reset(sysctl);
        break;

    case kInvalid:
    default:
        LOG("\ncommand not found");
        sysctl_event_reset(sysctl);
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
