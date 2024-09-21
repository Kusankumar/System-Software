#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signal) {
    if (signal == SIGALRM)
        printf("SIGALRM Received\n");
    else if (signal == SIGVTALRM)
        printf("SIGVTALRM Received\n");
    else if(signal == SIGPROF)
        printf("SIGPROF Received\n");
    else if(signal == SIGSEGV){
        printf("SIGSEGV Received\n");
        _exit(EXIT_SUCCESS);
    }
    else if(signal == SIGINT)
        printf("SIGINT Received\n");
    else if(signal == SIGFPE){
        printf("SIGFPE Received\n");
        _exit(EXIT_SUCCESS);
    }
}
