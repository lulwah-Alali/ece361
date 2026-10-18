#ifndef PTR_H
#define PTR_H

// Swaps the values of two floats.
void swap_float(float *a, float *b);

// Finds the minimum and maximum values.
int minmax(const float *a, int n, float *min, float *max);

// Finds the first value greater than threshold.
const float *find_above(const float *a, int n, float threshold);

// Reverses an array in place.
void reverse(float *a, int n);

#endif
