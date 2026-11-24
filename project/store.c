#include "store.h"
#include <stdlib.h>

typedef struct node {
    record_t record;
    struct node *left;
    struct node *right;
    size_t height;
} node_t;

struct store {
    node_t *root;
    size_t count;
};

int record_compare(const record_t *a,
                   const record_t *b)
{
    if (a->reading.timestamp < b->reading.timestamp)
        return -1;

    if (a->reading.timestamp > b->reading.timestamp)
        return 1;

    return 0;
}

static size_t node_height(const node_t *node)
{
    return node ? node->height : 0;
}

static void update_height(node_t *node)
{
    size_t left = node_height(node->left);
    size_t right = node_height(node->right);

    node->height = 1 + (left > right ? left : right);
}

static int balance(const node_t *node)
{
    return (int)node_height(node->left)
         - (int)node_height(node->right);
}

static node_t *rotate_right(node_t *node)
{
    node_t *left = node->left;

    node->left = left->right;
    left->right = node;

    update_height(node);
    update_height(left);

    return left;
}

static node_t *rotate_left(node_t *node)
{
    node_t *right = node->right;

    node->right = right->left;
    right->left = node;

    update_height(node);
    update_height(right);

    return right;
}

static node_t *insert_node(node_t *node,
                           const record_t *record,
                           int *result)
{
    if (!node) {
        node_t *new_node = malloc(sizeof(*new_node));

        if (!new_node) {
            *result = -1;
            return NULL;
        }

        new_node->record = *record;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 1;

        *result = 1;
        return new_node;
    }

    int cmp = record_compare(record, &node->record);

    if (cmp < 0) {
        node->left = insert_node(node->left,
                                 record, result);
    } else if (cmp > 0) {
        node->right = insert_node(node->right,
                                  record, result);
    } else {
        *result = 0;
        return node;
    }

    update_height(node);

    int b = balance(node);

    if (b > 1) {
        if (balance(node->left) < 0)
            node->left = rotate_left(node->left);

        return rotate_right(node);
    }

    if (b < -1) {
        if (balance(node->right) > 0)
            node->right = rotate_right(node->right);

        return rotate_left(node);
    }

    return node;
}

store_t *store_create(void)
{
    return calloc(1, sizeof(store_t));
}

int store_insert(store_t *store,
                 const record_t *record)
{
    if (!store || !record)
        return -1;

    int result = 0;

    store->root = insert_node(store->root,
                              record, &result);

    if (result == 1)
        store->count++;

    return result;
}

const record_t *store_find(const store_t *store,
                           time_t timestamp)
{
    if (!store)
        return NULL;

    const node_t *node = store->root;

    while (node) {
        if (timestamp < node->record.reading.timestamp)
            node = node->left;
        else if (timestamp > node->record.reading.timestamp)
            node = node->right;
        else
            return &node->record;
    }

    return NULL;
}

static void walk_node(const node_t *node,
                      store_callback_t callback,
                      void *context)
{
    if (!node)
        return;

    walk_node(node->left, callback, context);
    callback(&node->record, context);
    walk_node(node->right, callback, context);
}

void store_walk(const store_t *store,
                store_callback_t callback,
                void *context)
{
    if (store && callback)
        walk_node(store->root, callback, context);
}

size_t store_count(const store_t *store)
{
    return store ? store->count : 0;
}

size_t store_height(const store_t *store)
{
    return store ? node_height(store->root) : 0;
}

static void destroy_node(node_t *node)
{
    if (!node)
        return;

    destroy_node(node->left);
    destroy_node(node->right);

    free(node);
}

void store_destroy(store_t *store)
{
    if (!store)
        return;

    destroy_node(store->root);
    free(store);
}
