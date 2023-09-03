#ifndef _LIST_H_
#define _LIST_H_

#ifndef offsetof
/**
 * @brief 获取结构体成员MEMBER相对于结构体TYPE首地址的偏移量。
 * 就是假设把结构体放在0地址处，结构体首地址就是(TYPE *)0，那么通过这个首地址就可访问到MEMBER，
 * 此时MEMBER的地址就是偏移量。
 * 
 */
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef container_of
/**
 * @brief 通过结构体成员地址获取包含该成员的结构体的地址。即成员地址减去成员偏移
 * 
 * container_of - cast a member of a structure out to the containing structure
 * 
 * @param ptr the pointer to the member.
 * @param type the type of the container struct this is embedded in.
 * @param member the name of the member within the struct.
 * 
 */
#define container_of(ptr, type, member) ({                      \
		        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
			        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

/**
 * @brief 空指针
 * 
 */
#define LIST_POISON  ((void *)0)

/**
 * @brief 内核链表，双向链表
 * 
 * Simple doubly linked list implementation.
 * 
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 * 
 */
struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

/**
 * @brief 用于初始化链表节点name，将其两个成员初始化为节点自身的地址
 * 
 * (node)<--prev--node--next-->(node)
 * 
 * @param name 节点变量名
 * 
 */
#define LIST_HEAD_INIT(name) { &(name), &(name) }

/**
 * @brief 声明链表节点变量name并初始化链表节点
 * 
 * @param name 节点变量名
 * 
 */
#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

/**
 * @brief 初始化链表节点指针ptr指向的节点（PS：宏定义 do while 0 的用法）
 * 
 * @param ptr 节点指针
 * 
 */
#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/**
 * @brief 新节点new插在prev和next指向的两个节点之间，prev和next指向的节点必须存在，即使可能是同一个
 * 
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 * 
 * @param new 插入节点指针
 * @param prev 前继节点指针
 * @param next 后继节点指针
 */
static void __list_add(struct list_head *new,
            struct list_head *prev,
            struct list_head *next)
{
    next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/**
 * @brief 在节点head之后插入节点new。这个也叫做头插，意思是在头节点的后边插入新节点
 * 
 * list_add - add a new entry
 * 
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 * 
 * @param new new entry to be added
 * @param head list head to add it after
 */
static void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

/**
 * @brief 在节点head之前插入节点new。这个也叫做尾插，意思是在尾节点（头节点的前继）的后边插入新节点
 * 
 * list_add_tail - add a new entry
 * 
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 * 
 * @param new new entry to be added
 * @param head list head to add it before
 */
static void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

/**
 * @brief 删除prev和next指向的两个节点之间的节点
 * 
 * Delete a list entry by making the prev/next entries
 * point to each other.
 * 
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 * 
 * @param prev 前继节点指针
 * @param next 后继节点指针
 */
static void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * @brief 链表删除节点entry，删除后节点entry不能再访问。链表节点entry不能为空
 * 
 * list_del - deletes entry from list.
 * 
 * Note: list_empty on entry does not return true after this, the entry is
 * in an undefined state.
 * 
 * @param entry the element to delete from the list.
 */
static void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON;
	entry->prev = LIST_POISON;
}

/**
 * @brief 链表删除节点entry，删除后重新初始化节点entry。相当于将节点独立出链表作为新链表
 * 
 * list_del_init - deletes entry from list and reinitialize it.
 * 
 * @param entry the element to delete from the list.
 */
static void list_del_init(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry); 
}

/**
 * @brief 节点list移动到链表head上，节点list插入在节点head之后
 * 
 * list_move - delete from one list and add as another's head
 * 
 * @param list the entry to move
 * @param head the head that will precede our entry
 */
static void list_move(struct list_head *list, struct list_head *head)
{
        __list_del(list->prev, list->next);
        list_add(list, head);
}

/**
 * @brief 节点list移动到链表head上，节点list插入在节点head之前
 * 
 * list_move_tail - delete from one list and add as another's tail
 * 
 * @param list the entry to move
 * @param head the head that will follow our entry
 */
static void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
        __list_del(list->prev, list->next);
        list_add_tail(list, head);
}

/**
 * @brief 判断链表是否为空。链表只有头节点的时候，链表为空
 * 
 * list_empty - tests whether a list is empty
 * 
 * @param head the list to test.
 * @return int 
 */
static int list_empty(const struct list_head *head)
{
	return head->next == head;
}

/**
 * @brief 判断链表是否为空。同时检测链表的两个成员是否指向节点本身
 * 
 * list_empty_careful - tests whether a list is
 * empty _and_ checks that no other CPU might be
 * in the process of still modifying either member
 * 
 * @param head the list to test.
 * @return int 
 */
static int list_empty_careful(const struct list_head *head)
{
	struct list_head *next = head->next;
	return (next == head) && (next == head->prev);// next指向head且prev指向head
}

/**
 * @brief 将链表list整个插入在head节点之后
 * 
 * @param list 链表指针
 * @param head 链表指针
 */
static void __list_splice(struct list_head *list,
				 struct list_head *head)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;
	struct list_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}

/**
 * @brief 非空链表list所有节点插入链表head节点之后
 * 
 * list_splice - join two lists
 * 
 * @param list the new list to add.
 * @param head the place to add it in the first list.
 */
static void list_splice(struct list_head *list, struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head);
}

/**
 * @brief 非空链表list所有节点插入链表head节点之后。list重新初始化
 * 
 * list_splice_init - join two lists and reinitialise the emptied list.
 * 
 * The list at @list is reinitialised
 * 
 * @param list the new list to add.
 * @param head the place to add it in the first list.
 */
static inline void list_splice_init(struct list_head *list,
				    struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head);
		INIT_LIST_HEAD(list);
	}
}

/**
 * @brief 通过节点成员地址获取节点的地址
 * 
 * list_entry - get the struct for this entry
 * 
 * @param ptr the &struct list_head pointer.
 * @param type the type of the struct this is embedded in.
 * @param member the name of the list_struct within the struct.
 * 
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * @brief 顺序遍历链表。pos指向开始遍历的节点（非head），一直到head->prev
 * 
 * list_for_each	-	iterate over a list
 * 
 * @param pos the &struct list_head to use as a loop counter.
 * @param head the head for your list.
 * 
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * @brief 逆序遍历链表。pos指向开始遍历的节点（非head），一直到head->next
 * 
 * list_for_each_prev	-	iterate over a list backwards
 * 
 * @param pos the &struct list_head to use as a loop counter.
 * @param head the head for your list.
 * 
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * @brief 顺序遍历链表。支持在遍历时删除当前pos指向的节点。list_del中删除节点后会将pos指向
 * 节点的next和prev置为NULL，这样pos = pos->prev后pos为NULL，遍历出错。这里借助一个临时
 * 的n保存pos->next
 * 
 * list_for_each_safe	-	iterate over a list safe against removal of list entry
 * 
 * @param pos the &struct list_head to use as a loop counter.
 * @param n another &struct list_head to use as temporary storage
 * @param head the head for your list.
 * 
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

/**
 * @brief 顺序遍历以list_head作为成员的结构体S链表。pos是指向S的指针，head是pos指向
 * 的S中的list_head成员的地址，member是list_head成员的类型，即list_head
 * 
 * list_for_each_entry	-	iterate over list of given type
 * 
 * @param pos the type * to use as a loop counter.
 * @param head the head for your list.
 * @param member the name of the list_struct within the struct.
 * 
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member); \
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * @brief 逆序遍历以list_head作为成员的结构体S链表。pos是指向S的指针，head是pos指向
 * S中的list_head成员的地址，member是list_head成员的类型，即list_head
 * 
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * 
 * @param pos the type * to use as a loop counter.
 * @param head the head for your list.
 * @param member the name of the list_struct within the struct.
 * 
 */
#define list_for_each_entry_reverse(pos, head, member)				\
	for (pos = list_entry((head)->prev, typeof(*pos), member); \
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.prev, typeof(*pos), member))

/**
 * @brief 顺序遍历以list_head作为成员的结构体S链表。从pos指向的结构体S的下一个结构体开始遍历
 * 
 * list_for_each_entry_continue -	iterate over list of given type
 * 
 * @param pos the type * to use as a loop counter.
 * @param head the head for your list.
 * @param member the name of the list_struct within the struct.
 * 
 */
#define list_for_each_entry_continue(pos, head, member) 		\
	for (pos = list_entry(pos->member.next, typeof(*pos), member);			\
	     &pos->member != (head);					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * @brief 顺序遍历以list_head作为成员的结构体S链表。允许遍历过程中删除节点结构体
 * 
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * 
 * @param pos the type * to use as a loop counter.
 * @param n another type * to use as temporary storage
 * @param head the head for your list.
 * @param member the name of the list_struct within the struct.
 * 
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

#endif // _LIST_H_
