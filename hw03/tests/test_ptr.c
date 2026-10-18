#include <stdio.h>
#include "ptr.h"

static int passed = 0;
static int failed = 0;

static void check(int condition, const char *name)
{
    if (condition) {
        printf("PASS: %s\n", name);
        passed++;
    } else {
        printf("FAIL: %s\n", name);
        failed++;
    }
}

int main(void)
{
    float x = 2.0f, y = 5.0f;
    swap_float(&x, &y);
    check(x == 5.0f && y == 2.0f, "swap_float");

    float a[] = {3.0f, 1.0f, 7.0f, 2.0f};
    float min = 0.0f, max = 0.0f;

    check(minmax(a, 4, &min, &max) == 0 &&
          min == 1.0f && max == 7.0f, "minmax several");

    float single[] = {4.0f};
    check(minmax(single, 1, &min, &max) == 0 &&
          min == 4.0f && max == 4.0f, "minmax single");

    float old_min = min, old_max = max;
    check(minmax(a, 0, &min, &max) == -1 &&
          min == old_min && max == old_max, "minmax empty");

    check(minmax(NULL, 4, &min, &max) == -1 &&
          min == old_min && max == old_max, "minmax NULL");

    check(find_above(a, 4, 2.0f) == a, "find_above match");
    check(find_above(a, 4, 10.0f) == NULL, "find_above none");
    check(find_above(a, 4, 7.0f) == NULL, "find_above equal");

    reverse(a, 4);
    check(a[0] == 2.0f && a[1] == 7.0f &&
          a[2] == 1.0f && a[3] == 3.0f, "reverse even");

    float odd[] = {1.0f, 2.0f, 3.0f};
    reverse(odd, 3);
    check(odd[0] == 3.0f && odd[1] == 2.0f &&
          odd[2] == 1.0f, "reverse odd");

    printf("\n%d passed, %d failed\n", passed, failed);
    return failed ? 1 : 0;
}
