#include <stddef.h>
#include "ptr.h"

void swap_float(float *a, float *b)
{
    if (a == NULL || b == NULL)
        return;

    float temp = *a;
    *a = *b;
    *b = temp;
}
int minmax(const float *a, int n, float *min, float *max)
{
    if (a == NULL || n <= 0 || min == NULL || max == NULL)
        return -1;

    float smallest =*a;
    float largest = *a;

    for (int i = 1; i < n; i++) {
        if (*(a+i) < smallest)
            smallest = *(a+i);

        if (*(a+i) > largest)
            largest = *(a+i);
    }

    *min = smallest;
    *max = largest;

    return 0;
}
const float *find_above(const float *a, int n, float threshold)
{
    if (a == NULL || n <= 0)
        return NULL;

    for (int i = 0; i < n; i++) {
        if (*(a+i) > threshold)
            return a+i;
    }

    return NULL;
}
void reverse(float *a, int n)
{
    if (a == NULL || n <= 1)
        return;

    int left = 0;
    int right = n - 1;

    while (left < right) {
        float temp = *(a+left);
        *(a+left)=*(a+right);
        *(a+right) = temp;

        left++;
        right--;
    }
}
