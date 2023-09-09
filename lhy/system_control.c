#include <string.h>
#include <stdlib.h>

#include "system_control.h"

#include "login.h"
#include "utils.h"

// 系统控制变量初始化
void sysctl_init(SystemCtl *sysctl)
{
    memset(sysctl, 0, sizeof(SystemCtl));

    sysctl->bLogin = false;
    sysctl->accountInfoFilename = "./lhy/account_info";
    sysctl->cmdEvent = kNone;
    sysctl->processing = false;
    sysctl->errorInfo.errorCode = kSysOK;

    init_account_list(sysctl->accountInfoFilename, &sysctl->accountList);
}

void sysctl_get_curr_user_name(SystemCtl *sysctl, char *name)
{
    strncpy(name, sysctl->account.name, MAX_ACCOUNT_STRLEN);
}

void sysctl_show_curr_user_name(SystemCtl *sysctl)
{
    //LOGN("%s>", sysctl->account.name);
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

void sysctl_cmd_parse(SystemCtl *sysctl, const char *cmd)
{
    if (kNone != sysctl->cmdEvent)
        return;

    if (0 == strncmp("cls", cmd, MAX_CMD_STRLEN))
        sysctl->cmdEvent = kCls;
    else if (0 == strncmp("exit", cmd, MAX_CMD_STRLEN))
        sysctl->cmdEvent = kExit;
    else if (0 == strncmp("quit", cmd, MAX_CMD_STRLEN))
        sysctl->cmdEvent = kQuit;
    else if (0 == strncmp("login", cmd, MAX_CMD_STRLEN))
        sysctl->cmdEvent = kCmdLogin;
    else
        sysctl->cmdEvent = kInvalid;
}

void sysctl_event_reset(SystemCtl *sysctl)
{
    sysctl->cmdEvent = kNone;
    sysctl->processing = false;
}

// 命令行响应事件

// 登录事件
void event_login(SystemCtl *sysctl)
{
    if (kLoginInit == sysctl->eventStatus.loginStatus.status)
        return;

    Shell *shell = &sysctl->shell;
    LoginInfo *pLogin = &sysctl->eventStatus.loginStatus;

    switch (sysctl->eventStatus.loginStatus.status)
    {
    case kLoginAskId:
        LOGN("\ninput your name : ");
        pLogin->status = kLoginAskPwd;
        break;

    case kLoginAskPwd:
        if (strncmp("admin", shell->args[0], MAX_ACCOUNT_STRLEN))
        {
            pLogin->status = kLoginFailed;
            pLogin->errStr = "Login error : user name not match";
        }
        else
        {
            LOGN("input your pwd  : ");
            pLogin->status = kLoginCompPwd;
        }
        break;

    case kLoginCompPwd:
        if (strncmp("123456", shell->args[0], MAX_ACCOUNT_STRLEN))
        {
            pLogin->status = kLoginFailed;
            pLogin->errStr = "Login error : user password error";
        }
        else
        {
            // 登录成功
            sysctl->bLogin = true;
            pLogin->status = kLoginInit;
            sysctl_event_reset(sysctl);

            LOG("Login success");
        }
        break;

    case kLoginFailed:
        sysctl->errorInfo.errorCode = kSysLoginFailed;
        sysctl->errorInfo.errStr = pLogin->errStr;
        pLogin->status = kLoginInit;
        sysctl_event_reset(sysctl);
        break;

    case kLoginInit:
    default:
        break;
    }
}

void event_cls(SystemCtl *sysctl)
{
    system("cls");
    sysctl_show_curr_user_name(sysctl);
    sysctl_event_reset(sysctl);
}

void event_exit(SystemCtl *sysctl)
{
    system("cls");
    sysctl_logout(sysctl);
    sysctl_event_reset(sysctl);
}

void event_invalid(SystemCtl *sysctl)
{
    LOG("command not found");
    sysctl_event_reset(sysctl);
}

// 系统响应命令行时间，进入不同事件的处理流程
void sysctl_handle_event(SystemCtl *sysctl)
{
    switch (sysctl->cmdEvent)
    {
    case kCmdLogin:
        if (kLoginInit == sysctl->eventStatus.loginStatus.status)
        {
            sysctl->processing = true;
            sysctl->eventStatus.loginStatus.status = kLoginAskId;
        }
        event_login(sysctl);
        break;

    case kCls:
        event_cls(sysctl);
        break;

    case kExit:
        event_exit(sysctl);
        break;

    case kInvalid:
    default:
        event_invalid(sysctl);
        break;
    }
}

// 系统处理错误信息
void sysctl_handle_error(SystemCtl *sysctl)
{
    if (kSysOK == sysctl->errorInfo.errorCode)
        return;

    switch (sysctl->errorInfo.errorCode)
    {
    case kSysLoginFailed:
        LOGN(sysctl->errorInfo.errStr);
        sysctl->errorInfo.errorCode = kSysOK;
        break;

    default:
        break;
    }
}

void sysctl_polling(SystemCtl *sysctl)
{
    Shell shell;
    ShellArgs args;
    int argNums;
    int status = 1;

    shell_init(&shell);

    do
    {
        printf("> ");
        shell.read_line();
        args = shell.get_args();
        argNums = shell.get_args_nums();

        shell.args = shell.get_args();
        shell.argNums = shell.get_args_nums();
        sysctl->shell = shell;

        if (argNums)
        {
            sysctl_cmd_parse(sysctl, args[0]);
            sysctl_handle_event(sysctl);
        }

        sysctl_handle_error(sysctl);

        shell.destroy();
    } while (status);
}
