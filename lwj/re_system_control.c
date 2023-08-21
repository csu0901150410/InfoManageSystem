#include <stdio.h>
#include <stdlib.h>
 
#include "re_system_control.h"//已经引用了 "re_account_info.h"
#include "re_utils.h"

/**
 * @brief 系统控制变量初始化
 * 
 * @param systemctl 系统变量结构体指针
*/
void system_init(SystemCtl *systemctl)
{
    systemctl->blogin=false;//初始化为不登录
    systemctl->accountInfoFilename="account_info.txt";

    init_account_info(systemctl->accountInfoFilename,&systemctl->list);
}
 
 
