#include "../istack.h"
#include <stdio.h>
#include <stdlib.h>

static int passed = 0;
static int failed = 0;

#define CHECK(condition) do { \
    if (condition) { \
        printf("PASS: %s\n", #condition); \
        passed++; \
    } else { \
        printf("FAIL: %s\n", #condition); \
        failed++; \
    } \
} while (0)

int main(void) {
    istack_t *s = istack_create();

    CHECK(s != NULL);
    if (s == NULL) return 1;

    CHECK(istack_is_empty(s));
    CHECK(istack_count(s) == 0);
    CHECK(istack_capacity(s) == 8);

    int v = 123;

    CHECK(istack_pop(s, &v) == -1);
    CHECK(v == 123);

    CHECK(istack_peek(s, &v) == -1);
    CHECK(v == 123);

    for (int i = 0; i < 8; i++) {
        CHECK(istack_push(s, i) == 0);
    }

    CHECK(istack_capacity(s) == 8);
    CHECK(istack_push(s, 8) == 0);
    CHECK(istack_capacity(s) == 16);

    for (int i = 9; i < 1000; i++) {
        CHECK(istack_push(s, i) == 0);
    }

    CHECK(istack_count(s) == 1000);
    CHECK(istack_peek(s, &v) == 0);
    CHECK(v == 999);

    size_t n = 0;
    int *array = istack_to_array(s, &n);

    CHECK(array != NULL);
    CHECK(n == 1000);

    if (array != NULL) {
        CHECK(array[0] == 0);
        CHECK(array[999] == 999);

        array[0] = -100;
        free(array);
    }

    for (int i = 999; i >= 0; i--) {
        CHECK(istack_pop(s, &v) == 0);
        CHECK(v == i);
    }

    CHECK(istack_is_empty(s));
    CHECK(istack_capacity(s) >= 1000);

    istack_destroy(s);

    CHECK(istack_count(NULL) == 0);
    CHECK(istack_is_empty(NULL));
    CHECK(istack_capacity(NULL) == 0);
    CHECK(istack_push(NULL, 5) == -1);
    CHECK(istack_pop(NULL, &v) == -1);
    CHECK(istack_peek(NULL, &v) == -1);
    CHECK(istack_to_array(NULL, &n) == NULL);

    istack_t *a = istack_create();
    istack_t *b = istack_create();

    CHECK(a != NULL);
    CHECK(b != NULL);

    if (a != NULL && b != NULL) {
        CHECK(istack_push(a, 10) == 0);
        CHECK(istack_push(b, 20) == 0);

        CHECK(istack_peek(a, &v) == 0);
        CHECK(v == 10);

        CHECK(istack_peek(b, &v) == 0);
        CHECK(v == 20);
    }

    istack_destroy(a);
    istack_destroy(b);

    istack_t *c = istack_create();
    CHECK(c != NULL);

    if (c != NULL) {
        CHECK(istack_push(c, 50) == 0);
        istack_destroy(c);
    }

    printf("\nPassed: %d\n", passed);
    printf("Failed: %d\n", failed);

    return failed == 0 ? 0 : 1;
}
