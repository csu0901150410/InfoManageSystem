#ifndef _SYSTEM_CONTROL_H_
#define _SYSTEM_CONTROL_H_

#include "account_info.h"
#include "lhy_shell.h"

#define MAX_CMD_STRLEN 20

typedef enum
{
    kSysOK = 0,
    kSysLoginFailed,// 系统登录失败
} SystemErrorCode;

// 系统错误信息
typedef struct
{
    SystemErrorCode errorCode;
    char *errStr;
} SystemErrorInfo;

// 命令行指令类型枚举
typedef enum
{
    kNone = 0,
    kCmdLogin,
    kCls,// 清屏
    kExit,// 退出登录
    kQuit,// 退出系统
    kAddUser,// 增加用户

    kInvalid,
} CmdType;

// 各个命令行指令执行状态枚举
typedef enum
{
    kLoginInit = 0,// 登录初始状态
    kLoginAskId,// 登录请求账号
    kLoginAskPwd,// 登录请求密码
    kLoginCompPwd,// 登录比较密码
    kLoginFailed,// 登录失败
} LoginStatus;

typedef struct
{
    LoginStatus status;
    char *errStr;
} LoginInfo;

// 命令行事件执行状态
typedef struct
{
    union
    {
        LoginInfo loginStatus;
    };
    bool done;// 事件是否执行完成
} EventStatus;

typedef struct
{
    bool bLogin;// 是否登入
    AccountList accountList;// 账户列表
    AccountInfo account;// 当前登录账户

    char *accountInfoFilename;// 账密信息文件路径
    CmdType cmdEvent;

    Shell shell;
    int status;

    bool processing;// 系统是否在处理命令行指令

    SystemErrorInfo errorInfo;// 系统错误信息

    EventStatus eventStatus;// 系统命令行处理状态
} SystemCtl;

void sysctl_init(SystemCtl *sysctl);
bool sysctl_login(SystemCtl *sysctl);
void sysctl_deinit(SystemCtl *sysctl);
void sysctl_polling(SystemCtl *sysctl);

#endif // _SYSTEM_CONTROL_H_
