#include "report.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *values;
    size_t window;
    size_t count;
    size_t index;
    double sum;
} average_context_t;

static void average_callback(const record_t *record,
                             void *context)
{
    average_context_t *ctx = context;
    float temperature = record->reading.temperature;

    if (ctx->count >= ctx->window) {
        ctx->sum -= ctx->values[ctx->index];
    }

    ctx->values[ctx->index] = temperature;
    ctx->sum += temperature;

    ctx->index = (ctx->index + 1) % ctx->window;
    ctx->count++;

    if (ctx->count >= ctx->window) {
        printf("Time: %lld, Moving average: %.2f C\n",
               (long long)record->reading.timestamp,
               ctx->sum / ctx->window);
    }
}

void report_moving_average(const store_t *store,
                           size_t window)
{
    if (!store || window == 0)
        return;

    average_context_t ctx = {0};

    ctx.window = window;
    ctx.values = calloc(window, sizeof(float));

    if (!ctx.values)
        return;

    store_walk(store, average_callback, &ctx);

    free(ctx.values);
}
