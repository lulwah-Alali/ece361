#include "../tally.h"
#include <stdio.h>
#include <string.h>

static int passed = 0;
static int failed = 0;

static void check(int condition, const char *name)
{
    printf("%s: %s\n", condition ? "PASS" : "FAIL", name);
    if (condition)
        passed++;
    else
        failed++;
}

int main(void)
{
    tally_t *t = tally_create();
    check(t != NULL, "create");
    if (t == NULL)
        return 1;

    check(tally_size(t) == 0, "empty tally");
    check(tally_add(t, "cat") == 1, "add new name");
    check(tally_add(t, "cat") == 2, "count up");
    check(tally_count(t, "cat") == 2, "count existing");
    check(tally_count(t, "dog") == 0, "name never added");
    check(tally_add(t, "") == -1, "empty name");
    check(tally_add(t, NULL) == -1, "NULL name");
    check(tally_add(t, "123456789012345") == 1,
          "15 character name");
    check(tally_add(t, "1234567890123456") == -1,
          "16 character name");

    tally_destroy(t);
    check(tally_size(NULL) == 0, "NULL tally size");
    check(tally_count(NULL, "cat") == 0, "NULL tally count");
    tally_destroy(NULL);

    tally_t *a = tally_create();
    tally_t *b = tally_create();
    tally_t *c = tally_create();
    tally_t *d = tally_create();

    check(a && b && c && d, "TALLY_MAX limit");

    if (a) {
        for (int i = 0; i < TALLY_NAMES; i++) {
            char name[16];
            snprintf(name, sizeof(name), "name%02d", i);
            tally_add(a, name);
        }
        check(tally_size(a) == TALLY_NAMES, "full tally");
        check(tally_add(a, "extra") == -1, "full refuses new");
        check(tally_add(a, "name00") == 2,
              "existing name still counts");
    }

    tally_destroy(a);
    tally_destroy(b);
    tally_destroy(c);

    printf("Summary: %d passed, %d failed\n", passed, failed);
    return failed ? 1 : 0;
}
