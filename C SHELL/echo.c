#include "shell.h"
#include "builtin.h"

void builtin_echo(char **tokens) {
    int i = 1;
    int first = 1;
    while (tokens[i] != NULL) {
        if (!first) {
            printf(" ");
        }
        printf("%s", tokens[i]);
        first = 0;
        i++;
    }
    printf("\n");
}
