#include "shell.h"
#include "display.h"
#include "utils.h"
#include <limits.h>

void display_prompt() {
    char username[MAX_TOKEN_SIZE];
    char system_name[MAX_TOKEN_SIZE];
    char cwd[MAX_INPUT_SIZE];
    char rel_path[MAX_INPUT_SIZE];
    get_username(username);
    get_system_name(system_name);
    if (getcwd(cwd, sizeof(cwd)) == NULL) { // not understood 
        fprintf(stderr, "%sError: getcwd failed%s\n", COLOR_RED, COLOR_RESET);
        strcpy(rel_path, "~");
    } else {
        get_relative_path(cwd, rel_path);
    }
 
        printf("%s%s@%s%s:%s%s%s$ ",
           COLOR_GREEN, username, system_name, COLOR_RESET,
           COLOR_BLUE, rel_path, COLOR_RESET);
    fflush(stdout);
}

void get_relative_path(char *abs_path, char *rel_path) { // not understood
    int home_len = strlen(home_dir);
    if (strcmp(abs_path, home_dir) == 0) {
        strcpy(rel_path, "~");
    } else if (strncmp(abs_path, home_dir, home_len) == 0 && 
               abs_path[home_len] == '/') {
        sprintf(rel_path, "~%s", abs_path + home_len);
    } else {
        strcpy(rel_path, abs_path);
    }
}
