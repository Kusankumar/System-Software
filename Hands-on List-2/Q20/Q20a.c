/*
============================================================================
Name : Q20a.c
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
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main(){
    const char* path = "myfifo";
    if (mkfifo(path, 0666) == -1) {
        perror("mknod 1");
        exit(EXIT_FAILURE);
    }
    
    char wbuff[128];
    ssize_t bytes;
    printf("PID: %d\n",getpid());
    while (1)
    {
        int fd = open(path,O_RDWR);
        bytes = read(STDIN_FILENO,wbuff,sizeof(wbuff)-1);
        if(bytes>0)
            wbuff[bytes]='\0';
        write(fd,wbuff,sizeof(wbuff));
        memset(&wbuff,0,sizeof(wbuff));
        close(fd);
    }
    return 0;
}
/*
Output======================================================================
$ ./Q20a
PID: 11231
hi
what's up
============================================================================
*/