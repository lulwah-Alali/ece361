#ifndef TALLY_H
#define TALLY_H

#include <stdio.h>

#define TALLY_MAX 4
#define TALLY_NAMES 16
#define TALLY_LEN 15

typedef struct tally tally_t;

/* Creates an empty tally. Returns NULL if all slots are in use. */
tally_t *tally_create(void);

/* Releases a tally. NULL is allowed. */
void tally_destroy(tally_t *t);

/* Adds a name and returns its new count, or -1 on failure. */
int tally_add(tally_t *t, const char *name);

/* Returns the count of a name, or 0 if absent or t is NULL. */
int tally_count(const tally_t *t, const char *name);

/* Returns the number of different names, or 0 if t is NULL. */
int tally_size(const tally_t *t);

/* Prints names and counts in alphabetical order to out. */
void tally_print(const tally_t *t, FILE *out);

#endif
