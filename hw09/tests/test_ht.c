#include "../ht.h"
#include <stdio.h>

#define CHECK(x) do { \
    if (!(x)) { \
        printf("FAIL: %s\n", #x); \
        return 1; \
    } \
} while (0)

int main(void)
{
    CHECK(ht_create(0) == NULL);

    ht_t *t = ht_create(10);
    CHECK(t != NULL);
    CHECK(ht_size(t) == 0);
    CHECK(ht_longest_chain(t) == 0);
    ht_destroy(t);
    printf("PASS: empty table\n");

    t = ht_create(10);
    CHECK(t != NULL);
    CHECK(ht_add(t, 3) == 0);
    CHECK(ht_add(t, 3) == 0);
    CHECK(ht_add(t, 3) == 0);
    CHECK(ht_count(t, 3) == 3);
    CHECK(ht_size(t) == 1);
    ht_destroy(t);
    printf("PASS: repeated key\n");

    t = ht_create(10);
    CHECK(t != NULL);
    CHECK(ht_add(t, 5) == 0);
    CHECK(ht_add(t, 15) == 0);
    CHECK(ht_count(t, 5) == 1);
    CHECK(ht_count(t, 15) == 1);
    CHECK(ht_count(t, 25) == 0);
    CHECK(ht_longest_chain(t) == 2);
    ht_destroy(t);
    printf("PASS: collision\n");

    t = ht_create(10);
    CHECK(t != NULL);
    for (int i = 1; i <= 1000; i++) {
        CHECK(ht_add(t, i) == 0);
    }
    CHECK(ht_size(t) == 1000);
    CHECK(ht_longest_chain(t) == 100);
    ht_destroy(t);
    printf("PASS: 1000 keys\n");

    CHECK(ht_add(NULL, 1) == -1);
    CHECK(ht_count(NULL, 1) == 0);
    CHECK(ht_size(NULL) == 0);
    CHECK(ht_longest_chain(NULL) == 0);
    ht_destroy(NULL);
    printf("PASS: NULL arguments\n");

    printf("All tests passed!\n");
    return 0;
}
