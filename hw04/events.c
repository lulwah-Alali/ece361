#include "tally.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    tally_t *t = tally_create();
    char line[256];
    int lines = 0;
    int skipped = 0;
    int refused = 0;

    if (t == NULL)
        return 1;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);

        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        } else if (!feof(stdin)) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
        }

        if (line[0] == '\0' || line[0] == '#') {
            skipped++;
            continue;
        }

        lines++;

        if (tally_add(t, line) == -1)
            refused++;
    }

    tally_print(t, stdout);

    printf("lines %d names %d skipped %d refused %d\n",
           lines, tally_size(t), skipped, refused);

    tally_destroy(t);
    return 0;
}
