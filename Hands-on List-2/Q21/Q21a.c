/*
============================================================================
Name : Q21a.c
Author : Sonu Kumar Mahto

Description--------------------------
21. Write two programs so that both can communicate by FIFO -Use two way 
communications.

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
    const char* path1 = "myfifo1";
    const char* path2 = "myfifo2";
    if (mkfifo(path1, 0666) == -1) {
        perror("mknod 1");
        exit(EXIT_FAILURE);
    }
    
    char rbuff[128],wbuff[128];
    ssize_t bytes;
    printf("PID: %d\n",getpid());
    while (1)
    {
        int fd1 = open(path1,O_WRONLY);
        bytes = read(STDIN_FILENO,wbuff,sizeof(wbuff)-1);
        if(bytes>0)
            wbuff[bytes]='\0';
        write(fd1,wbuff,sizeof(wbuff));
        memset(&wbuff,0,sizeof(wbuff));
        close(fd1);

        int fd2 = open(path2,O_RDONLY);
        bytes = read(fd2,rbuff,sizeof(rbuff)-1);
        if(bytes>0)
            rbuff[bytes]='\0';
        write(STDOUT_FILENO,rbuff,sizeof(rbuff));
        memset(&rbuff,0,sizeof(wbuff));
        close(fd2);
    }
    return 0;
}
/*
Output======================================================================
$ ./Q21a
PID: 12287
hi
what's up
I'm sonu
============================================================================
*/