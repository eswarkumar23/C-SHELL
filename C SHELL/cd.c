#include "shell.h"
#include "builtin.h"
#include <limits.h>

void builtin_cd(char **tokens) {
{ // where cd .. is covered
    char cwd[MAX_INPUT_SIZE];
    char new_path[MAX_INPUT_SIZE];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        fprintf(stderr, "%sError: cd: getcwd failed%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    if (tokens[1] != NULL && tokens[2] != NULL)
    {
        fprintf(stderr, "%sError: cd: too many arguments%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    if (tokens[1] == NULL || strcmp(tokens[1], "~") == 0)
    {
        strcpy(new_path, home_dir);
    }
    else if (strcmp(tokens[1], "-") == 0)
    {
        if (strlen(prev_dir) == 0)
        {
            fprintf(stderr, "%sError: cd: No previous directory%s\n", COLOR_RED, COLOR_RESET);
            return;
        }
        strcpy(new_path, prev_dir);
        printf("%s%s%s\n", COLOR_BLUE, new_path, COLOR_RESET);
    }
    else
    {
        strcpy(new_path, tokens[1]);
    }

    if (chdir(new_path) != 0)
    {
        fprintf(stderr, "%sError: cd: %s%s\n", COLOR_RED, new_path, COLOR_RESET);
        return;
    }
    strcpy(prev_dir, cwd);
}
}