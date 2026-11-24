#ifndef AUX_H
#define AUX_H

#include <stddef.h>

typedef struct aux aux_t;

aux_t *aux_create(void);
int aux_add(aux_t *aux, float value);
size_t aux_count(const aux_t *aux);
size_t aux_count_at_or_above(const aux_t *aux,
                             float threshold);
void aux_destroy(aux_t *aux);

#endif
