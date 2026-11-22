#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct bst bst_t;

/* Creates an empty tree. Returns NULL if memory fails. */
bst_t *bst_create(void);

/* Frees all nodes and the tree. Accepts NULL. */
void bst_destroy(bst_t *t);

/* Adds a key. Returns 0 on success, -1 on failure. */
int bst_insert(bst_t *t, int key);

/* Checks for a key and counts visited nodes. */
bool bst_contains(const bst_t *t, int key, size_t *visits);

/* Returns the number of keys in the tree. */
size_t bst_size(const bst_t *t);

/* Returns the height of the tree. */
size_t bst_height(const bst_t *t);

/* Bonus: Removes one copy of a key. */
int bst_remove(bst_t *t, int key);

#endif
