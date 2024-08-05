#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void free_tree(t_btree *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void test_bstree_create_node() {
    t_btree *node1 = bstree_create_node(4);
    t_btree *node2 = bstree_create_node(7);

    if (node1 != NULL) {
        printf("Node 1 created with item: %d\n", node1->item);
    } else {
        printf("Failed to create Node 1\n");
    }

    if (node2 != NULL) {
        printf("Node 2 created with item: %d\n", node2->item);
    } else {
        printf("Failed to create Node 2\n");
    }

    free(node1);
    free(node2);
}

int main() {
    test_bstree_create_node();

    return 0;
}
