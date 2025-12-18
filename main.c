#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"
#include "q6.h"

int main(void) {

    char command[COMMAND_MAXSIZE] = {0};
    char *args[ARGS_MAXSIZE];

    // Set to -1 so the first prompt is simple (no previous command yet)
    int status = -1;

    display_welcome();
    display_exit_instruction();

    while(1) {

        display_status_and_time(status);

        int result = read_and_process_input(command);
            if (result == SHELL_EXIT) {
                break;
            }

            if (result == SHELL_CONTINUE) {

                find_arguments(command, args);

                timer_start();
                execute_complex_command(args, &status);
                timer_end();
            }
        }
    return 0;
}