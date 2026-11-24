#ifndef REPORT_H
#define REPORT_H

#include <stddef.h>
#include "store.h"

void report_moving_average(const store_t *store,
                           size_t window);

#endif
