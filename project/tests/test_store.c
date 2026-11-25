#include <assert.h>
#include <stdio.h>
#include "../store.h"

static void check_order(const record_t *record, void *context)
{
    time_t *expected = context;
    assert(record->reading.timestamp == *expected);
    (*expected)++;
}

int main(void)
{
    record_t a = {0};
    record_t b = {0};

    a.reading.timestamp = 1000;
    b.reading.timestamp = 1001;

    assert(record_compare(&a, &b) < 0);
    assert(record_compare(&b, &a) > 0);
    assert(record_compare(&a, &a) == 0);

    store_t *store = store_create();
    assert(store != NULL);
    assert(store_count(store) == 0);
    assert(store_height(store) == 0);

    store_destroy(store);

    store = store_create();
    assert(store != NULL);

    record_t record = {0};

    for (int i = 0; i < 100; i++) {
        record.reading.timestamp = 1000 + i;
        record.reading.temperature = 22.0 + i;

        assert(store_insert(store, &record) == 1);
        assert(store_count(store) == (size_t)(i + 1));

        if (i == 0)
            assert(store_height(store) == 1);

        if (i == 1)
            assert(store_height(store) == 2);
    }

    assert(store_count(store) == 100);
    assert(store_height(store) >= 7);
    assert(store_height(store) <= 9);

    const record_t *found = store_find(store, 1000);
    assert(found != NULL);
    assert(found->reading.temperature == 22.0);

    assert(store_find(store, 1099) != NULL);
    assert(store_find(store, 9999) == NULL);

    time_t expected = 1000;
    store_walk(store, check_order, &expected);
    assert(expected == 1100);

    store_destroy(store);

    printf("All store tests passed.\n");

    return 0;
}
