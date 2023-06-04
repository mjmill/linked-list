/*
 * Copyright (C) Matt Miller 2023
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>

struct num {
    int value;
    struct num *next;
};

struct root_num {
    struct num *start;
};

struct root_num root = { .start = NULL };

int initial_values[] = {1, 2, 3, 4, 5};
int expected_values[] = {2, 1, 4, 3, 5};

struct num *
create_num(int value)
{
    struct num *node = malloc(sizeof(struct num));

    if (node == NULL) {
        printf("%s: Failed to allocate a number structure.\n", __func__);
        goto out;
    }

    node->value = value;
    node->next = NULL;

out:
    return node;
}

void
insert_end(struct num *node)
{
    struct num *cur_node = root.start;

    if (cur_node == NULL) {
        root.start = node;
        goto out;
    }

    while (cur_node->next != NULL) {
        cur_node = cur_node->next;
    }

    cur_node->next = node;

out:
    return;
}

int
create_list(void)
{
    int ret = 0;
    unsigned long i;
    struct num *node;

    for (i = 0; i < (sizeof(initial_values) / sizeof(int)); i++) {
        node = create_num(initial_values[i]);
        if (node == NULL) {
            ret = 1;
            goto out;
        }
        insert_end(node);
    }

out:
    return ret;
}

void
print_list(void)
{
    struct num *cur_node = root.start;

    printf("%s: Current list: ", __func__);
    while (cur_node != NULL) {
        printf("%d", cur_node->value);
        cur_node = cur_node->next;
        if (cur_node != NULL) {
            printf(", ");
        }
    }
    printf("\n");
}

void
swap_elements_in_list(void)
{
    struct num *cur_node = root.start;
    struct num *next_node, **past_node = &root.start;

    while (cur_node != NULL && cur_node->next != NULL) {
        next_node = cur_node->next;
        cur_node->next = next_node->next;
        next_node->next = cur_node;
        *past_node = next_node;
        past_node = &cur_node->next;
        cur_node = cur_node->next;
    }
}

void
free_list(void)
{
    struct num *cur_node = root.start;
    struct num *tmp_node;

    root.start = NULL;

    while (cur_node != NULL) {
        tmp_node = cur_node->next;
        free(cur_node);
        cur_node = tmp_node;
    }
}

int
main(int argc, char const *argv[])
{
    if (create_list() != 0) {
        return -1;
    }

    printf("%s: Created a list.\n", __func__);

    print_list();

    swap_elements_in_list();

    print_list();

    free_list();

    print_list();
    
    return 0;
}