#include "shell.h"
#include "display.h"
#include "builtin.h"
#include "history.h"
#include "execute.h"
#include "redirection.h"
#include "signals.h"
#include "utils.h"
#include <limits.h>

char home_dir[MAX_INPUT_SIZE];
char prev_dir[MAX_INPUT_SIZE] = "";
pid_t foreground_pid = -1;


void init_shell() {
    if (getcwd(home_dir, sizeof(home_dir)) == NULL) {
        fprintf(stderr, "%sError: getcwd failed%s\n", COLOR_RED, COLOR_RESET);
        exit(EXIT_FAILURE);
    }
    init_signals();
    init_history();
}

void cleanup_shell() {
    save_history();
}

void process_command(char *input) {
    char *tokens[MAX_NUM_TOKENS];
    int token_count;
    int background = 0;
    input = trim_whitespace(input);// for extra or leading white spaces 
    if (strlen(input) == 0) {
        return;
    }
    add_to_history(input);
    token_count = tokenize(input, tokens);
    if (token_count == 0) {
        return;
    }
    background = is_background(tokens);
    if (background) {
        remove_background_token(tokens);
    }
    if (is_builtin(tokens)) {
        if (strcmp(tokens[0], "history") == 0) {
            display_history();
        } else {
            int should_exit = execute_builtin(tokens);
            if (should_exit) {
                cleanup_shell();
                exit(EXIT_SUCCESS);
            }
        }
    } else {
        if (has_redirection(tokens)) {
            execute_with_redirection(tokens, background);
        } else {
            execute_command(tokens, background);
        }
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    init_shell();
    while (1) {
        display_prompt();
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Ctrl+D pressed (EOF)
            printf("\n");
            break;
        }
        process_command(input);
    }
    cleanup_shell();
    return EXIT_SUCCESS;
}
