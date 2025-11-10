#include "shell.h"
#include "execute.h"
#include "redirection.h"

void execute_command(char **tokens, int background) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "%sError: fork failed%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    if (pid == 0) { // Child process
        if (background) {
            signal(SIGINT, SIG_IGN); // Ignore SIGINT in background processes
        }
        if (execvp(tokens[0], tokens) < 0) {
            fprintf(stderr, "%sError: %s: command not found%s\n", COLOR_RED, tokens[0], COLOR_RESET);
            exit(EXIT_FAILURE);
        }
    } else {
        if (background) {
            printf("[%d]\n", pid);
        } else {
            foreground_pid = pid;
            int status;
            waitpid(pid, &status, 0);
            foreground_pid = -1;
        }
    }
}

void execute_with_redirection(char **tokens, int background) { // not understood
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "%sError: fork failed%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    if (pid == 0) {
        if (background) {
            signal(SIGINT, SIG_IGN);
        }
        char *clean_tokens[MAX_NUM_TOKENS];
        if (setup_redirection(tokens, clean_tokens) < 0) {
            exit(EXIT_FAILURE);
        }
        if (execvp(clean_tokens[0], clean_tokens) < 0) {
            fprintf(stderr, "%sError: %s: command not found%s\n", COLOR_RED, clean_tokens[0], COLOR_RESET);
            exit(EXIT_FAILURE);
        }
    } else {
        
        if (background) {
            printf("[%d]\n", pid);
        } else {
            foreground_pid = pid;
            int status;
            waitpid(pid, &status, 0);
            foreground_pid = -1;
        }
    }
}
