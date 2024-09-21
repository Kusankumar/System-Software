/*
============================================================================
Name : Q20b.c
Author : Sonu Kumar Mahto

Description--------------------------
20. Write two programs so that both can communicate by FIFO -Use one way 
communication.

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main(){
    const char* path = "myfifo";

    char rbuff[128];
    ssize_t bytes;
    printf("PID: %d\n",getpid());
    while (1)
    {
        int fd = open(path,O_RDWR);
        bytes = read(fd,rbuff,sizeof(rbuff)-1);
        if(bytes>0);
            rbuff[bytes]='\0';
        write(STDOUT_FILENO,rbuff,sizeof(rbuff));
        memset(rbuff,0,sizeof(rbuff));
        close(fd);
    }
    return 0;
}
/*
Output======================================================================
$ ./Q20b
PID: 11232
hi
what's up
============================================================================
*/