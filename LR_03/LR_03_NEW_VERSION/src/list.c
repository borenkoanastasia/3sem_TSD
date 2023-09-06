#include "../inc/list.h"

list_el *new_elem_add_end(list_el *head, list_el *new_el)
{
    new_el->next = NULL;
    list_el *cur = head;
    if (!head)
    {
        return new_el;
    }
    for (; cur->next; cur = cur->next);
    cur->next = new_el;
    return head;
}

int create_list_el(list_el **el)
{
    *el = calloc(1, sizeof(list_el));
    if (!*el)
    {
        return ERROR_CREATE;
    }
    (*el)->next = NULL;
    return OK;
}

void free_list_el(list_el *el)
{
    free(el);
}

void free_list(list_el *head)
{
    list_el *next;
    for (; head;)
    {
        next = head->next;
        free_list_el(head);
        head = next;
    }
}
