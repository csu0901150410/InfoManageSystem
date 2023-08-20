
#include <stdarg.h>
#include <stdio.h>
#include "re_utils.h"

void LOG(const char* value,...)
{
    va_list args;//定义va_list类型的变量
    va_start(args,value);//arg指向可变参数的第一个参数
    vprintf(value,args);//输出
    va_end(args);
    
    printf("/n");

}