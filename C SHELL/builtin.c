#include "shell.h"
#include "builtin.h"

int is_builtin(char **tokens) {
    if (tokens[0] == NULL) {
        return 0;
    }
    if (strcmp(tokens[0], "echo") == 0 ||
        strcmp(tokens[0], "pwd") == 0 ||
        strcmp(tokens[0], "cd") == 0 ||
        strcmp(tokens[0], "history") == 0 ||
        strcmp(tokens[0], "exit") == 0) {
        return 1;
    }
    return 0;
}


int execute_builtin(char **tokens) {
    if (strcmp(tokens[0], "echo") == 0) {
        builtin_echo(tokens);
    } else if (strcmp(tokens[0], "pwd") == 0) {
        builtin_pwd();
    } else if (strcmp(tokens[0], "cd") == 0) {
        builtin_cd(tokens);
    } else if (strcmp(tokens[0], "exit") == 0) {
        return 1; 
    }
    
    return 0;
}
