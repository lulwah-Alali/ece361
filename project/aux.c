#include "aux.h"
#include <stdlib.h>

struct aux {
    float *values;
    size_t count;
    size_t capacity;
};

aux_t *aux_create(void)
{
    aux_t *aux = malloc(sizeof(*aux));
    if (!aux)
        return NULL;

    aux->count = 0;
    aux->capacity = 4;
    aux->values = malloc(4 * sizeof(float));

    if (!aux->values) {
        free(aux);
        return NULL;
    }

    return aux;
}

int aux_add(aux_t *aux, float value)
{
    if (!aux)
        return -1;

    if (aux->count == aux->capacity) {
        size_t capacity = aux->capacity * 2;
        float *temp = realloc(aux->values,
                              capacity * sizeof(float));

        if (!temp)
            return -1;

        aux->values = temp;
        aux->capacity = capacity;
    }

    size_t i = aux->count;

    while (i > 0 && aux->values[i - 1] > value) {
        aux->values[i] = aux->values[i - 1];
        i--;
    }

    aux->values[i] = value;
    aux->count++;

    return 0;
}

size_t aux_count(const aux_t *aux)
{
    return aux ? aux->count : 0;
}

size_t aux_count_at_or_above(const aux_t *aux,
                             float threshold)
{
    if (!aux)
        return 0;

    size_t low = 0;
    size_t high = aux->count;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (aux->values[mid] < threshold)
            low = mid + 1;
        else
            high = mid;
    }

    return aux->count - low;
}

void aux_destroy(aux_t *aux)
{
    if (aux) {
        free(aux->values);
        free(aux);
    }
}
