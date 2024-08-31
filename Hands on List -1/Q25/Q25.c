#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main() {
    pid_t c1, c2, c3;
    pid_t wpid;
    int status;

    c1 = fork();
    if (c1 == -1) {
        fprintf(stderr, "Failed to create Child 1: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } 
    else if (c1 == 0) {
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);
        exit(0);
    }

    c2 = fork();
    if (c2 == -1) {
        fprintf(stderr, "Failed to create Child 2: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } 
    else if (c2 == 0) {
        printf("Child 2: PID = %d\n", getpid());
        sleep(6); 
        exit(0);
    }

    c3 = fork();
    if (c3 == -1) {
        fprintf(stderr, "Failed to create Child 3: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } 
    else if (c3 == 0) {
        printf("Child 3: PID = %d\n", getpid());
        sleep(12); 
        exit(0);
    }

    printf("Parent waiting for  Child 2 (PID = %d)\n", c2);
    wpid = waitpid(c2, &status, 0);
    if (wpid == -1) {
        fprintf(stderr, "Failed to wait for Child 2: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } 
    else {
        if (WIFEXITED(status))
            printf("Child 2 exited with status = %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Child 2 was terminated by signal %d\n", WTERMSIG(status));
        else if (WIFSTOPPED(status))
            printf("stopped by signal %d\n", WSTOPSIG(status));
        else if (WIFCONTINUED(status))
            printf("continued\n");
        else 
            printf("Child 2 did not exit normally\n");
    }

    printf("Parent process Exited.\n");
    return 0;
}
/*===========================================================================
Output
$ ./main
Child 1: PID = 8166
Parent waiting for  Child 2 (PID = 8167)
Child 2: PID = 8167
Child 3: PID = 8168
Child 2 exited with status = 0
Parent process Exited.

*/
