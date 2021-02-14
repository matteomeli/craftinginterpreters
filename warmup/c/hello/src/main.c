#include <stdio.h>

#include "list.h"

int main()
{
    printf("Hello, C.\n");

    struct list *list = make_list();

    append(list, "C");
    append(list, "C++");
    append(list, "Rust");
    append(list, "VLang");
    append(list, "GoLang");

    print_list(list);

    erase_node(list, "VLang");

    print_list(list);

    struct list_node *node = remove_node(list, "C++");
    free_node(node);

    print_list(list);

    prepend(list, "Python");

    print_list(list);

    free_list(list);
}
