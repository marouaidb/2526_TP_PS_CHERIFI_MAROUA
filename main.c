#include "q1.h"
#include "q2.h"
#include "q3.h"

int main(void) {

    char command[MAX_COMMAND_SIZE] = {0};
    int status = 0;

    display_welcome();
    display_exit_instruction();

    while(1) {
        display_prompt();
        int result = read_and_process_input(command);

            if (result == SHELL_EXIT) {
                break;
            }

            if (result == SHELL_CONTINUE) {
                execute_command(command, &status);
            }
        }
    return 0;
}