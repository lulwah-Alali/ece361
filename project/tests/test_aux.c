#include <assert.h>
#include <stdio.h>
#include "../aux.h"

int main(void)
{
    aux_t *aux = aux_create();
    assert(aux != NULL);

    assert(aux_count(aux) == 0);

    aux_add(aux, 20.0);
    aux_add(aux, 25.0);
    aux_add(aux, 30.0);
    aux_add(aux, 35.0);

    assert(aux_count(aux) == 4);
    assert(aux_count_at_or_above(aux, 25.0) == 3);
    assert(aux_count_at_or_above(aux, 35.0) == 1);
    assert(aux_count_at_or_above(aux, 40.0) == 0);

    aux_destroy(aux);

    printf("All aux tests passed.\n");

    return 0;
}
