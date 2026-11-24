#include <assert.h>
#include <stdio.h>
#include "../report.h"
#include "../store.h"

int main(void)
{
    store_t *store = store_create();
    assert(store != NULL);

    record_t record = {0};

    for (int i = 0; i < 5; i++) {
        record.reading.timestamp = 1000 + i;
        record.reading.temperature = 20.0f + i;
        record.reading.humidity = 50.0f;

        store_insert(store, &record);
    }

    assert(store_count(store) == 5);

    report_moving_average(store, 3);

    store_destroy(store);

    return 0;
}
