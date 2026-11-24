#include <assert.h>
#include <stdio.h>
#include "../store.h"

int main(void)
{
    store_t *store = store_create();
    assert(store != NULL);

    record_t record = {0};

    record.reading.timestamp = 1000;
    record.reading.temperature = 22.0;
    store_insert(store, &record);

    record.reading.timestamp = 1001;
    record.reading.temperature = 25.0;
    store_insert(store, &record);

    assert(store_count(store) == 2);

    const record_t *found = store_find(store, 1000);
    assert(found != NULL);
    assert(found->reading.temperature == 22.0);

    assert(store_find(store, 9999) == NULL);

    store_destroy(store);

    printf("All store tests passed.\n");

    return 0;
}
