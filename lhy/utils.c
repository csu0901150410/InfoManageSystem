#include <stdarg.h>
#include <stdio.h>

void LOG(const char* fmt, ...)
{
	va_list args;       //定义一个va_list类型的变量，用来储存单个参数  
	va_start(args, fmt); //使args指向可变参数的第一个参数  
	vprintf(fmt, args);  //必须用vprintf等带V的  
	va_end(args);       //结束可变参数的获取

	printf("\n");
}

void LOGN(const char* fmt, ...)
{
	va_list args;       //定义一个va_list类型的变量，用来储存单个参数  
	va_start(args, fmt); //使args指向可变参数的第一个参数  
	vprintf(fmt, args);  //必须用vprintf等带V的  
	va_end(args);       //结束可变参数的获取
}