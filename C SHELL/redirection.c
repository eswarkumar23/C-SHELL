#include "shell.h"
#include "redirection.h"
#include <fcntl.h>

int has_redirection(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

int setup_redirection(char **tokens, char **clean_tokens) { // not understood
    int i = 0;
    int clean_idx = 0;
    char *input_file = NULL;
    char *output_file = NULL;
    while (tokens[i] != NULL) {
        if (strcmp(tokens[i], "<") == 0) {
            if (tokens[i + 1] == NULL) {
                fprintf(stderr, "%sError: No input file specified%s\n", COLOR_RED, COLOR_RESET);
                return -1;
            }
            input_file = tokens[i + 1];
            i += 2;
        } else if (strcmp(tokens[i], ">") == 0) {
            if (tokens[i + 1] == NULL) {
                fprintf(stderr, "%sError: No output file specified%s\n", COLOR_RED, COLOR_RESET);
                return -1;
            }
            output_file = tokens[i + 1];
            i += 2;
        } else {
            clean_tokens[clean_idx++] = tokens[i];
            i++;
        }
    }
    clean_tokens[clean_idx] = NULL;
    
    if (input_file != NULL) {
        int fd = open(input_file, O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "%sError: Input redirection: cannot open %s%s\n", COLOR_RED, input_file, COLOR_RESET);
            return -1;
        }
        if (dup2(fd, STDIN_FILENO) < 0) {
            fprintf(stderr, "%sError: dup2 input failed%s\n", COLOR_RED, COLOR_RESET);
            close(fd);
            return -1;
        }
        close(fd);
    }
    
    if (output_file != NULL) {
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            fprintf(stderr, "%sError: Output redirection: cannot open %s%s\n", COLOR_RED, output_file, COLOR_RESET);
            return -1;
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {
            fprintf(stderr, "%sError: dup2 output failed%s\n", COLOR_RED, COLOR_RESET);
            close(fd);
            return -1;
        }
        close(fd);
    }
    
    return 0;
}
