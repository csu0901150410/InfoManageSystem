#ifndef _RE_SYSTEM_CONTROL_H
#define _RE_SYSTEM_CONTROL_H

#include "re_account_info.h"
#define MAX_CMD_STRLEN 15

//枚举指令识别
typedef enum
{
    KNone=0,
    kExit,//退出登录
    KCls,//清屏
    KQuit,//退出系统
}cmdType;

typedef struct 
{
    bool blogin;//是否登录
    AccountInfo login_info;//当前登录账户
    AccountList list;//账户
    cmdType  cmd;

    char *accountInfoFilename;//账密信息文件路径
}SystemCtl;

void system_init(SystemCtl *systemctl);



#endif
