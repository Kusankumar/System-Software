#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];  
    int pipe2[2];  
    pid_t pid1, pid2;

    pipe(pipe1) ;

    pid1 = fork();

    

    if (pid1 == 0) {
        // Child 1 

        dup2(pipe1[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe1[1]); 

        execlp("ls", "ls", "-l", NULL);
        return(1);
    }

    pipe(pipe2);

    pid2 = fork();


    if (pid2 == 0) {
        // Child 2

        dup2(pipe1[0], STDIN_FILENO);

        dup2(pipe2[1], STDOUT_FILENO);

        close(pipe1[0]); 
        close(pipe1[1]); 
        close(pipe2[0]); 
        close(pipe2[1]); 

        execlp("grep", "grep", "^d", NULL);

    }

    // Parent 

    close(pipe1[0]); 
    close(pipe1[1]); 
    close(pipe2[1]); 

    dup2(pipe2[0], STDIN_FILENO);

    close(pipe2[0]);

    execlp("wc", "wc", NULL);


    return 0;
}