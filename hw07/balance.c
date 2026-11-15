#include "istack.h"
#include <stdio.h>
#include <stdlib.h>

static int is_open(int c) {
    return c == '(' || c == '[' || c == '{';
}

static int is_close(int c) {
    return c == ')' || c == ']' || c == '}';
}

static int matching(int c) {
    if (c == ')') return '(';
    if (c == ']') return '[';
    return '{';
}

static int closing(int c) {
    if (c == '(') return ')';
    if (c == '[') return ']';
    return '}';
}

int main(void) {
    istack_t *s = istack_create();
    if (s == NULL) {
        fprintf(stderr, "memory error\n");
        return 1;
    }

    int c;
    int top;
    size_t line = 1, col = 0;
    size_t pairs = 0, deepest = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line++;
            col = 0;
            continue;
        }

        col++;

        if (is_open(c)) {
            if (istack_push(s, c) != 0) {
                istack_destroy(s);
                fprintf(stderr, "memory error\n");
                return 1;
            }

            if (istack_count(s) > deepest) {
                deepest = istack_count(s);
            }

        } else if (is_close(c)) {
            if (istack_is_empty(s)) {
                printf("line %zu, column %zu: found '%c', nothing open\n",
                       line, col, c);
                istack_destroy(s);
                return 1;
            }

            istack_peek(s, &top);

            if (top != matching(c)) {
                printf("line %zu, column %zu: found '%c', expected '%c'\n",
                       line, col, c, closing(top));
                istack_destroy(s);
                return 1;
            }

            istack_pop(s, &top);
            pairs++;
        }
    }

    if (!istack_is_empty(s)) {
        istack_peek(s, &top);
        printf("end of input: %zu still open, innermost '%c'\n",
               istack_count(s), top);
        istack_destroy(s);
        return 1;
    }

    printf("balanced: %zu pairs, deepest %zu\n", pairs, deepest);
    istack_destroy(s);
    return 0;
}
