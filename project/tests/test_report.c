#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../report.h"
#include "../store.h"

static void check_report(store_t *store, const char *expected)
{
    char output[512] = {0};

    assert(freopen("report_test.tmp", "w", stdout) != NULL);

    report_moving_average(store, 3);
    fflush(stdout);

    FILE *file = fopen("report_test.tmp", "r");
    assert(file != NULL);

    fread(output, 1, sizeof(output) - 1, file);
    fclose(file);

    assert(strcmp(output, expected) == 0);
}

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

        if (i == 1)
            check_report(store, "");

        if (i == 2)
            check_report(store,
                "Time: 1002, Moving average: 21.00 C\n");

        if (i == 4)
            check_report(store,
                "Time: 1002, Moving average: 21.00 C\n"
                "Time: 1003, Moving average: 22.00 C\n"
                "Time: 1004, Moving average: 23.00 C\n");
    }

    assert(store_count(store) == 5);

    store_destroy(store);
    fclose(stdout);
    remove("report_test.tmp");

    fprintf(stderr, "All report tests passed.\n");

    return 0;
}
