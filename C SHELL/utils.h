#ifndef UTILS_H
#define UTILS_H

int tokenize(char *input, char **tokens);
char *trim_whitespace(char *str);
int is_background(char **tokens);
void remove_background_token(char **tokens);
void get_username(char *username);
void get_system_name(char *system_name);

#endif 
