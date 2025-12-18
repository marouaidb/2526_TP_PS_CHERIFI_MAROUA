#ifndef QUESTION6_H
#define QUESTION6_H

// Prevent overflow
#define ARGS_MAXSIZE 1024

void find_arguments(char *command, char **args);
void execute_complex_command(char **command, int *status);


#endif //QUESTION6_H