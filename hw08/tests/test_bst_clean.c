#include "../bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    bst_t *tree = bst_create();

    if (tree == NULL) {
        printf("FAIL: create\n");
        return 1;
    }

    int keys[] = {27, 14, 35, 10, 19, 31, 42};

    for (int i = 0; i < 7; i++) {
        if (bst_insert(tree, keys[i]) != 0) {
            printf("FAIL: insert\n");
            bst_destroy(tree);
            return 1;
        }
    }

    size_t visits = 0;

    if (bst_size(tree) != 7 ||
        bst_height(tree) != 3 ||
        !bst_contains(tree, 31, &visits) ||
        visits != 3) {
        printf("FAIL: basic tree\n");
        bst_destroy(tree);
        return 1;
    }

    printf("PASS: basic tree\n");

bst_destroy(tree);
return 0;
}
