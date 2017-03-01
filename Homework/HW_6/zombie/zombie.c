/* Matthew Blanchard
 * ECE 331
 * zombie.c
 *       A C program which creates zombies. Creates a child process, sends
 *       a term signal, then exits after 10 seconds. Child waits in an endless loop
 *     afterward.
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

void child_process(void);

int main()
{
        pid_t child;
        
        child = fork();
        if (child == -1) {
                printf("Error: Failed to create child process...\n");
                return -1;
        } else if (child == 0) {
                child_process();
                printf("The child process failed to wait.\n");
                return -2;
        } else {
                printf("Child process created, PID is %d...\n", child);
                kill(child, SIGTERM);
                sleep(10);
                return 0;
        }
}

void child_process(void)
{
        while(1)
                sleep(2);
        return;
}

