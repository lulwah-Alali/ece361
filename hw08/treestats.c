#include "bst.h"
#include <stdio.h>

int main(void)
{
    bst_t *tree = bst_create();

    if (tree == NULL) {
        return 1;
    }

    int key;
    int count = 0;

    while (scanf("%d", &key) == 1) {
        if (bst_insert(tree, key) != 0) {
            bst_destroy(tree);
            return 1;
        }
        count++;
    }

    if (!feof(stdin)) {
        printf("not a number after %d values\n", count);
        bst_destroy(tree);
        return 1;
    }

    if (count == 0) {
        printf("empty tree\n");
        bst_destroy(tree);
        return 0;
    }

    printf("n %zu, height %zu\n",
           bst_size(tree), bst_height(tree));

    bst_destroy(tree);
    return 0;
}
