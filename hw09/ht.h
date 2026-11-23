#ifndef HT_H
#define HT_H

#include <stddef.h>

typedef struct ht ht_t;  /* opaque */

/* Creates an empty hash table with nbuckets buckets.
   Returns NULL if nbuckets is 0 or memory fails. */
ht_t *ht_create(size_t nbuckets);

/* Frees all memory used by the table.
   Does nothing if t is NULL. */
void ht_destroy(ht_t *t);

/* Adds one count for key.
   Returns 0 on success, -1 on failure. */
int ht_add(ht_t *t, int key);

/* Returns how many times key was added.
   Returns 0 if not found or t is NULL. */
size_t ht_count(const ht_t *t, int key);

/* Returns the number of different keys.
   Returns 0 if t is NULL. */
size_t ht_size(const ht_t *t);

/* Returns the number of nodes in the longest chain.
   Returns 0 if empty or t is NULL. */
size_t ht_longest_chain(const ht_t *t);

#endif
