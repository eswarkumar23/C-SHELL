#include "shell.h"
#include "builtin.h"
#include <limits.h>

void builtin_pwd() {
    char cwd[MAX_INPUT_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        fprintf(stderr, "%sError: pwd: cannot get current directory%s\n", COLOR_RED, COLOR_RESET);
    }
}
