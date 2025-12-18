#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"
#include "q6.h"
#include "q7.h"

// Find the redirection symbol and return its type and position 
int find_redirection(char **args, int *position) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0)  { 
            *position = i; 
            return REDIR_IN; 
        }
        if (strcmp(args[i], ">") == 0)  {
            *position = i; 
            return REDIR_OUT;
        }
        // if (strcmp(args[i], "|") == 0)  {
        //     *position = i; 
        //     return PIPE; 
        // }
    }
    return REDIR_NONE;
}

// Configure file descriptors for redirection 
void apply_redirection(char **args, int position, int type) {
    int fd;

    // Get the file name for redirection
    char *file = args[position + 1];

    if (type == REDIR_IN) {

        // Open file for reading
        fd = open(file, O_RDONLY);
    } 
    else {

        // Open file for writing (create/truncate)
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, WRITE_OWNER_PERMISSION);
    }

    if (fd == -1) {

        // Print error if file cannot be opened
        perror("open"); 

        // If file descriptor fails, terminate
        exit(EXIT_FAILURE); 
    }
    
    // Redirect STDIN or STDOUT
    dup2(fd, (type == REDIR_IN) ? STDIN_FILENO : STDOUT_FILENO);

    // Close the original file descriptor
    close(fd);
    
    // Truncate args to hide the redirection from execvp
    args[position] = NULL;
}

void execute_complex_command_redir(char **args, int *status) {
    int position = 0;

    // Identify if there is a redirection before forking 
    int type = find_redirection(args, &position);

    // Create a new process
    pid_t pid = fork();

    // Child process: execute the command
    if (pid == 0) {  

        // If a redirection exists, apply it inside the child
        if (type == REDIR_IN || type == REDIR_OUT) {
            apply_redirection(args, position, type);
        }

        // Execute the command 
        execvp(args[0], args);
        
        // Print an error message if execvp fails
        perror("enseash"); 

        // If execlp fails, terminate child to avoid running parent code
        exit(EXIT_FAILURE);
    } 
    else {
        
        // Parent process: wait for the child to finish          
        wait(status);
    }
}