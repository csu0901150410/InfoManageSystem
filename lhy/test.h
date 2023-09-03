#ifndef _TEST_H_
#define _TEST_H_

/**
 * @file test.h
 * @author lhy (lianghongyu.csu@gmail.com)
 * @brief 测试文件。用于测试各个功能模块，测试代码可放到该文件实现。
 * @version 0.1
 * @date 2023-08-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "list.h"

typedef struct list_head list;

// 结构体定义，其中包含一个内核链表成员
typedef struct
{
    int data;
    list list;
} TestList;

void test_list(void);

#endif // _TEST_H_
