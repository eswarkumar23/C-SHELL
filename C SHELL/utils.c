#include "shell.h"
#include "utils.h"
#include <pwd.h>
#include <ctype.h>

int tokenize(char *input, char **tokens) {
    int count = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL && count < MAX_NUM_TOKENS - 1) {
        tokens[count++] = token;
        token = strtok(NULL, " \t\n");// iternally it remember the next part of the string 
    }
    tokens[count] = NULL;
    return count;
}

char *trim_whitespace(char *str) { // should remove internal spaces too
    char *end;
    while (isspace((unsigned char)*str)) 
    str++;
    if (*str == 0) 
    return str; // entire string was whitespace
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
    end--;
    end[1] = '\0';
    return str;
}

int is_background(char **tokens) { 
    int i = 0;
    while (tokens[i] != NULL) {
        i++;
    }
    if (i > 0 && strcmp(tokens[i - 1], "&") == 0) {
        return 1;
    }
    return 0;
}

void remove_background_token(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        i++;
    }
    if (i > 0 && strcmp(tokens[i - 1], "&") == 0) {
        tokens[i - 1] = NULL;
    }
}

void get_username(char *username) {
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL) {
        strcpy(username, pw->pw_name);
    } else {
        strcpy(username, "unknown");
    }
}

void get_system_name(char *system_name) {
    if (gethostname(system_name, MAX_TOKEN_SIZE) != 0) {
        strcpy(system_name, "unknown");
    }
}
