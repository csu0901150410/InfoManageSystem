#include "system_control.h"

/**
 * @brief 更新说明
 * 
 * 2023081201--修复用户列表销毁的bug，增加登录功能
 * 2023081401--增加指令识别模块，还待完善
 * 2023081501--指令事件处理后将事件清零，增加清屏、退出登录指令
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