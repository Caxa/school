#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node* init(const struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node) {
        new_node->door = *door;
        new_node->next = NULL;
    }
    return new_node;
}

struct node* add_door(struct node* elem, struct door* door) {
    if (elem == NULL) return NULL;

    struct node* new_node = init(door);
    if (new_node) {
        new_node->next = elem->next;
        elem->next = new_node;
    }
    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        if (current->door.id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (root == NULL || elem == NULL) return root;
    if (root == elem) {
        struct node* next_node = root->next;
        free(root);
        return next_node;
    }

    struct node* current = root;
    while (current->next != NULL && current->next != elem) {
        current = current->next;
    }

    if (current->next == elem) {
        current->next = elem->next;
        free(elem);
    }
    return root;
}

void destroy(struct node* root) {
    struct node* current = root;
    struct node* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}
