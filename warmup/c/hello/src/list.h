#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

struct list_node
{
    struct list_node *prev;
    struct list_node *next;
    char *data;
};

struct list
{
    struct list_node *first;
    struct list_node *last;
};

struct list *make_list();
void free_list(struct list *list);

struct list_node *make_node(char *data);
void free_node(struct list_node *node);

void prepend(struct list *list, char *data);
void append(struct list *list, char *data);

void insert_before(struct list *list, struct list_node *node, char *data);
void insert_after(struct list *list, struct list_node *node, char *data);

struct list_node *find(struct list *list, char *data);
struct list_node *remove_node(struct list *list, char *data);
void erase_node(struct list *list, char *data);

void traverse_forward(struct list *list, void fn(struct list_node *));
void traverse_backward(struct list *list, void fn(struct list_node *));

size_t length(struct list *list);

void print_node(struct list_node *node);
void print_list(struct list *list);

struct list *make_list()
{
    struct list *list = (struct list *)malloc(sizeof(*list));
    if (!list)
    {
        printf("Cannot allocate memory for a new list.");
        return NULL;
    }
    return list;
}

void free_list(struct list *list)
{
    if (!list)
    {
        return;
    }

    struct list_node *node = list->first;
    while (node)
    {
        struct list_node *next = node->next;
        free_node(node);
        node = next;
    }

    free(list);
    list = NULL;
}

struct list_node *make_node(char *data)
{
    struct list_node *node = (struct list_node *)malloc(sizeof(*node));
    if (!node)
    {
        printf("Cannot allocate memory for a new list node.");
        return NULL;
    }

    node->data = strdup(data);

    return node;
}

void free_node(struct list_node *node)
{
    if (!node)
    {
        return;
    }

    if (node->data)
    {
        free(node->data);
    }

    free(node);
    node = NULL;
}

void prepend(struct list *list, char *data)
{
    if (!list)
    {
        return;
    }

    if (!list->first)
    {
        struct list_node *node = make_node(data);
        if (!node)
        {
            return;
        }

        list->first = node;
        list->last = node;
        node->next = NULL;
        node->prev = NULL;
    }
    else
    {
        insert_before(list, list->first, data);
    }
}

void append(struct list *list, char *data)
{
    if (!list)
    {
        return;
    }

    if (!list->last)
    {
        struct list_node *node = make_node(data);
        if (!node)
        {
            return;
        }

        list->first = node;
        list->last = node;
        node->next = NULL;
        node->prev = NULL;
    }
    else
    {
        insert_after(list, list->last, data);
    }
}

void insert_before(struct list *list, struct list_node *node, char *data)
{
    if (!list)
    {
        return;
    }

    struct list_node *new_node = make_node(data);
    if (!new_node)
    {
        return;
    }

    new_node->next = node;
    if (!node->prev)
    {
        new_node->prev = NULL;
        list->first = new_node;
    }
    else
    {
        new_node->prev = node->prev;
        node->prev->next = new_node;
    }
    node->prev = new_node;
}

void insert_after(struct list *list, struct list_node *node, char *data)
{
    if (!list)
    {
        return;
    }

    struct list_node *new_node = make_node(data);
    if (!new_node)
    {
        return;
    }

    new_node->prev = node;
    if (!node->next)
    {
        new_node->next = NULL;
        list->last = new_node;
    }
    else
    {
        new_node->next = node->next;
        node->next->prev = new_node;
    }
    node->next = new_node;
}

struct list_node *find(struct list *list, char *data)
{
    if (!list || !data)
    {
        return NULL;
    }

    struct list_node *node = list->first;
    while (node)
    {
        if (strcmp(node->data, data) == 0)
        {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

struct list_node *remove_node(struct list *list, char *data)
{
    if (!list || !data)
    {
        return NULL;
    }

    struct list_node *node = list->first;
    while (node)
    {
        if (strcmp(node->data, data) == 0)
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->next = NULL;
            node->prev = NULL;
            return node;
        }
        node = node->next;
    }

    return NULL;
}

void erase_node(struct list *list, char *data)
{
    struct list_node *node = remove_node(list, data);
    free_node(node);
}

void traverse_forward(struct list *list, void fn(struct list_node *))
{
    if (!list)
    {
        return;
    }

    struct list_node *node = list->first;
    while (node)
    {
        fn(node);
        node = node->next;
    }
}

void traverse_backward(struct list *list, void fn(struct list_node *))
{
    if (!list || !fn)
    {
        return;
    }

    struct list_node *node = list->last;
    while (node)
    {
        fn(node);
        node = node->prev;
    }
}

size_t length(struct list *list)
{
    if (!list || !list->first)
    {
        return 0;
    }

    size_t length = 0;
    struct list_node *node = list->first;
    while (node)
    {
        length++;
        node = node->next;
    }

    return length;
}

void print_node(struct list_node *node)
{
    printf("%s", node->data);
    if (node->next)
    {
        printf(", ");
    }
}

void print_list(struct list *list)
{
    printf("{ ");
    traverse_forward(list, print_node);
    printf(" } ");
    printf("(%ld)\n\n", length(list));
}

#endif // LIST_H
