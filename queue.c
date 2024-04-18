#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue
 * Good to be back
 */
struct list_head *q_new()
{
    /* Allocate memory to for a new list head */
    struct list_head *head = malloc(1 * sizeof(struct list_head));
    if (head == NULL)
        return NULL;  // Return NULL if memory allcation fails
    // Initialize the list head to point to itself to form an empty list
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        if (entry != NULL)
            free(entry->value);
        free(entry);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (head == NULL)
        return false;
    element_t *next_ele = malloc(sizeof(element_t));
    if (next_ele == NULL)
        return false;
    next_ele->value = strdup(s);
    list_add(&next_ele->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (head == NULL)
        return false;
    element_t *next_ele = malloc(sizeof(element_t));
    if (next_ele == NULL)
        return false;
    next_ele->value = strdup(s);
    list_add_tail(&next_ele->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || head->next == head)
        return NULL;
    struct list_head *node = head->next;
    element_t *ele = list_entry(node, element_t, list);
    list_del(node);
    if (sp != NULL && bufsize > 0) {
        strncpy(sp, ele->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return ele;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || head->next == head)
        return NULL;
    struct list_head *node = head->prev;
    element_t *ele = list_entry(node, element_t, list);
    list_del(node);
    if (sp != NULL && bufsize > 0) {
        strncpy(sp, ele->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return ele;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;

    struct list_head *first = head->next;
    struct list_head *second = head->prev;
    while ((first != second) && (first->next != second)) {
        first = first->next;
        second = second->prev;
    }
    element_t *node = list_entry(first, element_t, list);
    list_del(first);
    free(node->value);
    free(node);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;

    bool dup = false;
    element_t *cur, *tmp;
    list_for_each_entry_safe (cur, tmp, head, list) {
        if (&tmp->list != head && !strcmp(cur->value, tmp->value)) {
            free(cur->value);
            list_del(&cur->list);
            free(cur->value);
            free(cur);
            dup = true;
        } else if (dup) {
            free(cur->value);
            list_del(&cur->list);
            free(cur->value);
            free(cur);
            dup = false;
        }
    }
    return true;
}
/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head || list_empty(head))
        return;
    struct list_head *first, *second;
    list_for_each_safe (first, second, head) {
        if (second == head)
            break;
        first->prev->next = second;
        second->prev = first->prev;
        first->next = second->next;
        first->prev = second;
        second->next->prev = first;
        second->next = first;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    struct list_head *prev = head;
    struct list_head *curr = head->next;

    while (curr != head) {
        curr->prev = curr->next;
        curr->next = prev;
        prev = curr;
        curr = curr->prev;
    }
    curr->prev = curr->next;
    curr->next = prev;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
