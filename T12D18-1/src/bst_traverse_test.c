#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void print_node(int value) { printf("%d ", value); }
void free_tree(t_btree *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void test_bstree_traversals() {
    t_btree *root = NULL;

    bstree_insert(&root, 4, compare);
    bstree_insert(&root, 2, compare);
    bstree_insert(&root, 6, compare);
    bstree_insert(&root, 1, compare);
    bstree_insert(&root, 3, compare);
    bstree_insert(&root, 5, compare);
    bstree_insert(&root, 7, compare);

    printf("Infix traversal: ");
    bstree_apply_infix(root, print_node);
    printf("\n");

    printf("Prefix traversal: ");
    bstree_apply_prefix(root, print_node);
    printf("\n");

    printf("Postfix traversal: ");
    bstree_apply_postfix(root, print_node);
    printf("\n");

    free_tree(root);
}

int main() {
    test_bstree_traversals();
    return 0;
}
