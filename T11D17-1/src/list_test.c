#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

int test_add_door() {
    struct door door1 = {1, 0};
    struct door door2 = {2, 0};
    struct node* list = init(&door1);
    add_door(list, &door2);
    find_door(2, list);
    if (list->next == NULL || list->next->door.id != 2) {
        destroy(list);
        return FAIL;
    }

    destroy(list);
    return SUCCESS;
}

int test_remove_door() {
    struct door door1 = {1, 0};
    struct door door2 = {4, 0};

    struct node* list = init(&door1);
    add_door(list, &door2);
    list = remove_door(list->next, list);

    if (list->next != NULL) {
        destroy(list);
        return FAIL;
    }

    destroy(list);
    return SUCCESS;
}

int main() {
    if (test_add_door() == SUCCESS) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }

    if (test_remove_door() == SUCCESS) {
        printf("\nSUCCESS");
    } else {
        printf("\nFAIL");
    }

    return 0;
}
