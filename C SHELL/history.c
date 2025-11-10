#include "shell.h"
#include "history.h"

#define HISTORY_FILE ".mysh_history"
static char *history[HISTORY_SIZE];
static int history_count = 0;
static int history_start = 0;

void init_history()
{ // some part not understood
    char history_path[MAX_INPUT_SIZE];
    /* Guard against possible truncation when home_dir is large */
    size_t needed = strlen(home_dir) + 1 + strlen(HISTORY_FILE) + 1; /* slash + null */
    if (needed > sizeof(history_path)) {
        fprintf(stderr, "%sError: home_dir too long to build history path%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    snprintf(history_path, sizeof(history_path), "%s/%s", home_dir, HISTORY_FILE);
    FILE *fp = fopen(history_path, "r");
    if (fp == NULL)
    {
        return;
    }
    char line[MAX_INPUT_SIZE];
    while (fgets(line, sizeof(line), fp) != NULL && history_count < HISTORY_SIZE)
    {
        line[strcspn(line, "\n")] = 0;
        history[history_count] = strdup(line);
        history_count++;
    }
    fclose(fp);
}

void add_to_history(char *command)
{ // some part not understood
    if (command == NULL || strlen(command) == 0)
    {
        return;
    }
    if (history_count > 0)
    {
        int prev_idx = (history_start + history_count - 1) % HISTORY_SIZE; // we can keep if history[0] then check for history[19]
        if (strcmp(history[prev_idx], command) == 0)
        {
            return;
        }
    }
    if (history_count == HISTORY_SIZE)
    {
        free(history[history_start]);
        history[history_start] = strdup(command);
        history_start = (history_start + 1) % HISTORY_SIZE;
    }
    else
    {
        history[history_count] = strdup(command);
        history_count++;
    }
    save_history();
}

void display_history()
{
    int start = 0;
    if (history_count > HISTORY_DISPLAY)
        start = history_count - HISTORY_DISPLAY;
    for (int i = start; i < history_count; i++)
    {
        int idx = (history_start + i) % HISTORY_SIZE;
        printf("%s%s%s\n", COLOR_YELLOW, history[idx], COLOR_RESET);
    }
}

void save_history()
{
    char history_path[MAX_INPUT_SIZE];
    /* Guard against possible truncation when home_dir is large */
    size_t needed = strlen(home_dir) + 1 + strlen(HISTORY_FILE) + 1; /* slash + null */
    if (needed > sizeof(history_path)) {
        fprintf(stderr, "%sError: home_dir too long to build history path%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    snprintf(history_path, sizeof(history_path), "%s/%s", home_dir, HISTORY_FILE);

    FILE *fp = fopen(history_path, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "%sError: save_history: cannot open history file%s\n", COLOR_RED, COLOR_RESET);
        return;
    }

    for (int i = 0; i < history_count; i++)
    {
        int idx = (history_start + i) % HISTORY_SIZE;
        fprintf(fp, "%s\n", history[idx]);
    }

    fclose(fp);
}
