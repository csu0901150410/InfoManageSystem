#include "system_control.h"

/**
 * @brief 更新说明
 * 
 * 2023081201--修复用户列表销毁的bug，增加登录功能
 * 
 */

int main()
{
    SystemCtl sysctl;
    sysctl_init(&sysctl);
    sysctl_login(&sysctl);
    sysctl_deinit(&sysctl);
    return 0;
}