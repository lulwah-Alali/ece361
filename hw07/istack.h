#ifndef ISTACK_H
#define ISTACK_H

#include <stddef.h>
#include <stdbool.h>

#define ISTACK_START 8

typedef struct istack istack_t;

/* Creates an empty stack. Returns NULL if memory fails. */
istack_t *istack_create(void);

/* Frees all memory used by the stack. */
void istack_destroy(istack_t *s);

/* Adds a value to the stack. Returns 0 on success. */
int istack_push(istack_t *s, int v);

/* Removes the top value. Returns -1 on failure. */
int istack_pop(istack_t *s, int *v);

/* Reads the top value without removing it. */
int istack_peek(const istack_t *s, int *v);

/* Returns the number of values in the stack. */
size_t istack_count(const istack_t *s);

/* Returns true if the stack is empty. */
bool istack_is_empty(const istack_t *s);

/* Returns the current capacity of the stack. */
size_t istack_capacity(const istack_t *s);

/* Copies the stack into a new array, bottom first. */
int *istack_to_array(const istack_t *s, size_t *n);

#endif
