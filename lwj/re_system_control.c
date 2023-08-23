#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
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
    systemctl->cmd = KNone;//指令初始化为0；
    init_account_list(systemctl->accountInfoFilename,&systemctl->list);
}

/**
 * @brief  系统控制变量取当前用户的账号名
 * 
 * @param systemctl 系统控制变量
*/
void system_get_curr_user_name(SystemCtl *systemctl,char *name)
{
    //？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
    //复制systemctl->login.name到name
    strncpy(name,systemctl->login_info.name,MAX_ACCOUNT_STRLEN);
}

void system_show_curr_name(SystemCtl *systemctl)
{
    LOG("%s>>>",systemctl->login_info.name);
}
 
/**
 * @brief 系统变量 登录
*/
 bool systemctl_login(SystemCtl *systemctl)
 {
   if(systemctl->blogin)//登录
      return true;
    
 }
 
