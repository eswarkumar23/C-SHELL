#include "shell.h"
#include "signals.h"
#include "display.h"


void init_signals() {
    
    signal(SIGINT, handle_sigint);
    signal(SIGCHLD, handle_sigchld);
}

void handle_sigint(int sig) {
    (void)sig; 
    if (foreground_pid > 0) {
        kill(foreground_pid, SIGKILL);
    } else {
        /* No foreground process - just redisplay prompt */
        const char nl = '\n';
        ssize_t r = write(STDOUT_FILENO, &nl, 1);
        (void)r;
        /* Redisplay the prompt */
        display_prompt();
    }
}

void handle_sigchld(int sig) {
    (void)sig; 
    while (waitpid(-1, NULL, WNOHANG) > 0) {
    }
}
