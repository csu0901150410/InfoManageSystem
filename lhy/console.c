#include "system_control.h"

/**
 * @brief 更新说明
 * 
 * 2023081201--修复用户列表销毁的bug，增加登录功能
 * 2023081401--增加指令识别模块，还待完善
 * 
 */

int main()
{
    SystemCtl sysctl;
    sysctl_init(&sysctl);

    sysctl_polling(&sysctl);

    sysctl_deinit(&sysctl);
    return 0;
}