#ifndef _SYSTEM_CONTROL_H_
#define _SYSTEM_CONTROL_H_

#include "account_info.h"

typedef struct
{
    bool bLogin;// 是否登入
    AccountList accountList;// 账户列表
    AccountInfo account;// 当前登录账户

    char *accountInfoFilename;// 账密信息文件路径
} SystemCtl;

void sysctl_init(SystemCtl *sysctl);
void sysctl_login(SystemCtl *sysctl);
void sysctl_deinit(SystemCtl *sysctl);

#endif // _SYSTEM_CONTROL_H_
