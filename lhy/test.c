#include "test.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief 这里介绍内核链表的基本使用。
 * 
 * 之前的单链表，存在数据域指针域的说法，用户数据成员和链表指针成员是混在一起的，这限制了链表的通用化，
 * 对于不同的用户数据的链表需要重写链表的逻辑。而内核链表通过在用户数据结构中加入链表节点成员实现了
 * 链表的逻辑，既然用户数据在链表数据结构内部无法通用，那就让链表数据结构在用户数据结构内。
 * 
 * 简单说，就是内核链表完成链式的逻辑，将内核链表节点作为用户数据结构的一个成员，专门负责链表逻辑，
 * 这很河里。
 * 
 */

/**
 * @brief 链表尾插
 * 
 * @param head 链表头指针
 * @param new 节点指针
 */
static void list_append(struct list_head *head, void *new)
{
	list_add((new), (head)->prev);
}

/**
 * @brief 链表头插
 * 
 * @param head 链表头指针
 * @param new 节点指针
 */
static void list_prepend(struct list_head *head, void *new)
{
	list_add(new, head);
}

/**
 * list_size - Returns the size (in number of entries) of the
 * supplied list.
 *
 * @head: The pointer to the head of the list to count the items in.
 **/
static unsigned int list_size(struct list_head *head)
{
	unsigned int count = 0;
	struct list_head *pos;
	list_for_each(pos, head)
		count++;
	return count;
}

// 定义内核链表的第一种方法
//static list test_list_head = LIST_HEAD_INIT(test_list_head);

void test_list(void)
{
    // 定义内核链表的第二种方法
    list test_list_head;
    INIT_LIST_HEAD(&test_list_head);

    // 定义目标结构体
    TestList node1, node2, node3;
    node1.data = 1;
    node2.data = 2;
    node3.data = 3;

    // 链表尾插
    list_append(&test_list_head, &node1.list);
    list_append(&test_list_head, &node2.list);
    list_append(&test_list_head, &node3.list);

    // 链表长度
    printf("list size : %d\n", list_size(&test_list_head));

    // 遍历目标结构体链表
    TestList *pos;// 临时的结构体变量，在for循环中遍历指向链表上的目标结构体
    list_for_each_entry(pos, &test_list_head, list)
    {
        // 对链表上目标结构体的惭操作
        printf("%d\n", pos->data);
    }
}
