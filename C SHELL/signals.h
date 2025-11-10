#ifndef SIGNALS_H
#define SIGNALS_H

void init_signals();
void handle_sigint(int sig);
void handle_sigchld(int sig);

#endif 
