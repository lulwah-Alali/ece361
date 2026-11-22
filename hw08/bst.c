#include "bst.h"
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node_t;

struct bst {
    node_t *root;
};

/* Creates an empty tree. */
bst_t *bst_create(void)
{
    bst_t *t = malloc(sizeof(bst_t));

    if (t == NULL) {
        return NULL;
    }

    t->root = NULL;
    return t;
}

static void free_nodes(node_t *node)
{
    if (node == NULL) {
        return;
    }

    free_nodes(node->left);
    free_nodes(node->right);
    free(node);
}

void bst_destroy(bst_t *t)
{
    if (t == NULL) {
        return;
    }

    free_nodes(t->root);
    free(t);
}

int bst_insert(bst_t *t, int key)
{
    if (t == NULL) {
        return -1;
    }

    node_t **current = &t->root;

    while (*current != NULL) {
        if (key < (*current)->key) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }

    node_t *new_node = malloc(sizeof(node_t));

    if (new_node == NULL) {
        return -1;
    }

    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    *current = new_node;
    return 0;
}

bool bst_contains(const bst_t *t, int key, size_t *visits)
{
    if (visits != NULL) {
        *visits = 0;
    }

    if (t == NULL) {
        return false;
    }

    node_t *current = t->root;

    while (current != NULL) {
        if (visits != NULL) {
            (*visits)++;
        }

        if (key == current->key) {
            return true;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

static size_t count_nodes(const node_t *node)
{
    if (node == NULL) {
        return 0;
    }

    return 1 + count_nodes(node->left)
             + count_nodes(node->right);
}

size_t bst_size(const bst_t *t)
{
    if (t == NULL) {
        return 0;
    }

    return count_nodes(t->root);
}

static size_t node_height(const node_t *node)
{
    if (node == NULL) {
        return 0;
    }

    size_t left = node_height(node->left);
    size_t right = node_height(node->right);

    return 1 + (left > right ? left : right);
}

size_t bst_height(const bst_t *t)
{
    if (t == NULL) {
        return 0;
    }

    return node_height(t->root);
}

int bst_remove(bst_t *t, int key)
{
    if (t == NULL) {
        return -1;
    }

    node_t **current = &t->root;

    while (*current != NULL && (*current)->key != key) {
        if (key < (*current)->key) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }

    if (*current == NULL) {
        return -1;
    }

    node_t *temp = *current;

    if (temp->left == NULL) {
        *current = temp->right;
        free(temp);
    } else if (temp->right == NULL) {
        *current = temp->left;
        free(temp);
    } else {
        node_t **next = &temp->right;

        while ((*next)->left != NULL) {
            next = &(*next)->left;
        }

        temp->key = (*next)->key;
        node_t *remove_node = *next;
        *next = remove_node->right;
        free(remove_node);
    }

    return 0;
}
