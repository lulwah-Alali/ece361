#include "../bst.h"
#include <stdio.h>

int main(void) {
    bst_t *tree = bst_create();

    int keys[] = {27, 14, 35, 10, 19, 31, 42};

    for (int i = 0; i < 7; i++) {
        bst_insert(tree, keys[i]);
    }

    if (bst_remove(tree, 10) != 0 ||
        bst_size(tree) != 6) {
        printf("FAIL: remove leaf\n");
        return 1;
    }

    if (bst_remove(tree, 14) != 0 ||
        bst_size(tree) != 5) {
        printf("FAIL: remove node\n");
        return 1;
    }

    if (bst_remove(tree, 27) != 0 ||
        bst_size(tree) != 4) {
        printf("FAIL: remove root\n");
        return 1;
    }

    printf("PASS: bonus remove\n");
    bst_destroy(tree);
    return 0;
}
