#ifndef _SYSTEM_CONTROL_H_
#define _SYSTEM_CONTROL_H_

#include "account_info.h"

#define MAX_CMD_STRLEN 20

typedef enum
{
    kNone = 0,
    kEnter,// 单独回车
    kCls,// 清屏
    kExit,// 退出登录
    kQuit,// 退出系统

    kInvalid,
} CmdType;

typedef struct
{
    bool bLogin;// 是否登入
    AccountList accountList;// 账户列表
    AccountInfo account;// 当前登录账户

    char *accountInfoFilename;// 账密信息文件路径
    CmdType cmdEvent;
} SystemCtl;

void sysctl_init(SystemCtl *sysctl);
bool sysctl_login(SystemCtl *sysctl);
void sysctl_deinit(SystemCtl *sysctl);
void sysctl_polling(SystemCtl *sysctl);

#endif // _SYSTEM_CONTROL_H_
