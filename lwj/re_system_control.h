#ifndef _RE_SYSTEM_CONTROL_H
#define _RE_SYSTEM_CONTROL_H

#include "re_account_info.h"

typedef struct 
{
    bool blogin;//是否登录
    AccountInfo login_info;//当前登录账户
    AccountList list;//账户

    char *accountInfoFilename;//账密信息文件路径


}SystemCtl;



#endif
