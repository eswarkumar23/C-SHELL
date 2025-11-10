#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 4096
#define MAX_TOKEN_SIZE 256
#define MAX_NUM_TOKENS 64
#define HISTORY_SIZE 20
#define HISTORY_DISPLAY 10


#define COLOR_GREEN  "\033[1;32m"
#define COLOR_BLUE   "\033[1;34m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RED    "\033[1;31m"
#define COLOR_RESET  "\033[0m"

extern char home_dir[MAX_INPUT_SIZE];  // global home directory path
extern char prev_dir[MAX_INPUT_SIZE];  // to track previous directory for cd -
extern pid_t foreground_pid; // to track foreground process ID  so signal handler kill it 


void init_shell();
void cleanup_shell();

#endif 
