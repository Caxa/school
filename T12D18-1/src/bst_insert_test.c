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

void test_bstree_insert() {
    t_btree *root = NULL;

    bstree_insert(&root, 4, compare);
    printf("Inserted 4 at root\n");

    bstree_insert(&root, 2, compare);
    printf("Inserted 2 to the left of 4\n");

    bstree_insert(&root, 6, compare);
    printf("Inserted 6 to the right of 4\n");

    bstree_insert(&root, 1, compare);
    printf("Inserted 1 to the left of 2\n");

    bstree_insert(&root, 3, compare);
    printf("Inserted 3 to the right of 2\n");

    bstree_insert(&root, 5, compare);
    printf("Inserted 5 to the left of 6\n");

    bstree_insert(&root, 7, compare);
    printf("Inserted 7 to the right of 6\n");

    free_tree(root);
}
int main() {
    test_bstree_insert();

    return 0;
}
