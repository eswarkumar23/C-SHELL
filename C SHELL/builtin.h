#ifndef BUILTIN_H
#define BUILTIN_H

int is_builtin(char **tokens);
int execute_builtin(char **tokens);
void builtin_echo(char **tokens);
void builtin_pwd();
void builtin_cd(char **tokens);

#endif 

