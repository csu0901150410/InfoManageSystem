#include "test.h"

#include <stdlib.h>

void test_list(void)
{
    List *head = list_node_create(NULL, 0);

    list_insert_tail(head, list_node_create(NULL, 1));
    list_insert_tail(head, list_node_create(NULL, 2));
    list_insert_tail(head, list_node_create(NULL, 3));

    list_print_list(head);
    list_destroy(&head);
}
