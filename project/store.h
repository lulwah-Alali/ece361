#ifndef STORE_H
#define STORE_H

#include <stddef.h>
#include <stdint.h>
#include "sensor.h"
#include "fsm.h"

typedef struct {
    reading_t reading;
    state_t state;
    uint32_t status;
} record_t;

typedef struct store store_t;

typedef void (*store_callback_t)(
    const record_t *record, void *context);

int record_compare(const record_t *a,
                   const record_t *b);

store_t *store_create(void);

int store_insert(store_t *store,
                 const record_t *record);

const record_t *store_find(
    const store_t *store, time_t timestamp);

void store_walk(const store_t *store,
                store_callback_t callback,
                void *context);

size_t store_count(const store_t *store);

size_t store_height(const store_t *store);

void store_destroy(store_t *store);

#endif
