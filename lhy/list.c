#include "list.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief 链表节点创建
 * 
 * @param next 链表指针域
 * @param data 链表数据域
 * @return List* 返回创建的链表节点指针
 */
List *list_node_create(List *next, int data)
{
    List *node = malloc(sizeof(List));
    node->next = next;
    node->data = data;
    return node;
}

/**
 * @brief 获取链表尾节点
 * 
 * @param head 链表头指针
 * @return List* 返回链表尾节点指针
 */
List *list_get_tail(List *head)
{
    List *node = head;
    while (1)
    {
        if (!node->next)
            break;
        node = node->next;
    }
    return node;
}

/**
 * @brief 链表尾插
 * 
 * @param head 链表头指针
 * @param node 插入的链表节点指针
 */
void list_insert_tail(List *head, List *node)
{
    List *tail = list_get_tail(head);
    tail->next = node;
}

/**
 * @brief 链表节点打印
 * 
 * @param node 链表节点指针
 */
void list_print_node(List *node)
{
    printf("Node : ptr-%p data-%d\n", node, node->data);
}

/**
 * @brief 链表打印
 * 
 * @param head 链表头指针
 */
void list_print_list(List *head)
{
    List *node = head->next;
    while (1)
    {
        if (!node)
            break;

        list_print_node(node);
        node = node->next;
    }
}

/**
 * @brief 链表销毁
 * 
 * @param root 链表头指针地址
 */
void list_destroy(List **root)
{
    List *curr = *root;
    while (1)
    {
        if (!curr)
            break;

        List *next = curr->next;
        free(curr);
        curr = next;
    }
    *root = NULL;
}
