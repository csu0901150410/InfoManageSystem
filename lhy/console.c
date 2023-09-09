#include "system_control.h"

#include "test.h"

/**
 * @brief 更新说明
 * 
 * 2023081201--修复用户列表销毁的bug，增加登录功能
 * 2023081401--增加指令识别模块，还待完善
 * 2023081501--指令事件处理后将事件清零，增加清屏、退出登录指令
 * 2023081601--实现一个简单的shell
 * 2023082801--实现一个简单的链表
 * 2023090301--移植linux内核链表
 * 2023090901--shell介入命令行响应逻辑，初步重做系统登录功能
 * 
 */

int main()
{
    //test_list();
    
    SystemCtl sysctl;
    sysctl_init(&sysctl);

    sysctl_polling(&sysctl);

    sysctl_deinit(&sysctl);

    return 0;
}