
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[41];
    int count;
    unsigned int priority;
    struct Node *left, *right;
} Node;

static unsigned int seed = 123456789;

unsigned int random_priority(void) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

int size(Node *root) {
    return root ? root->count : 0;
}

void update(Node *root) {
    if (root)
        root->count = 1 + size(root->left) + size(root->right);
}

Node *merge(Node *a, Node *b) {
    if (!a) return b;
    if (!b) return a;

    if (a->priority < b->priority) {
        a->right = merge(a->right, b);
        update(a);
        return a;
    }

    b->left = merge(a, b->left);
    update(b);
    return b;
}

void split(Node *root, int k, Node **a, Node **b) {
    if (!root) {
        *a = NULL;
        *b = NULL;
        return;
    }

    int left = size(root->left);

    if (k <= left) {
        split(root->left, k, a, &root->left);
        *b = root;
        update(root);
    } else {
        split(root->right, k - left - 1, &root->right, b);
        *a = root;
        update(root);
    }
}

Node *remove_at(Node *root, int index, Node **removed) {
    Node *a, *b, *c;
    split(root, index, &a, &b);
    split(b, 1, removed, &c);
    return merge(a, c);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: ./pie k\n");
        return 1;
    }

    char *end;
    long long k = strtoll(argv[1], &end, 10);

    if (*argv[1] == '\0' || *end != '\0' ||
        k < 1 || k > 2000000000LL) {
        fprintf(stderr, "usage: ./pie k\n");
        return 1;
    }

    Node *root = NULL;
    char line[256];
    int n = 0;

    while (fgets(line, sizeof(line), stdin)) {
        size_t len = strlen(line);

        while (len > 0 &&
               (line[len - 1] == '\n' ||
                line[len - 1] == '\r')) {
            line[--len] = '\0';
        }

        if (len == 0) continue;

        Node *node = malloc(sizeof(Node));
        if (!node) return 1;

        snprintf(node->name, sizeof(node->name), "%s", line);
        node->count = 1;
        node->priority = random_priority();
        node->left = NULL;
        node->right = NULL;

        root = merge(root, node);
        n++;
    }

    if (n == 0) {
        printf("no guests: more pie for the cook.\n");
        return 0;
    }

    long long pos = 0;

    while (n > 1) {
        pos = (pos + (k - 1) % n) % n;

        Node *removed = NULL;
        root = remove_at(root, (int)pos, &removed);

        printf("couch: %s\n", removed->name);
        free(removed);
        n--;

        if (pos == n) pos = 0;
    }

    printf("last slice: %s\n", root->name);
    free(root);

    return 0;
}

