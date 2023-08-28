#ifndef _LIST_H_
#define _LIST_H_

// 单链表，带头节点
typedef struct node
{
    struct node *next;
    int data;
} List;

List *list_node_create(List *next, int data);
List *list_get_tail(List *head);
void list_insert_tail(List *head, List *node);
void list_print_node(List *node);
void list_print_list(List *head);
void list_destroy(List **root);

#endif // _LIST_H_
