/*
============================================================================
Name : Q22.c
Author : Sonu Kumar Mahto

Description--------------------------
22. Write a program to wait for data to be written into FIFO within 10 seconds,
use select system call with FIFO.

Date: 15 Sept, 2024
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include <stdlib.h>
#include<sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main(){
    fd_set fds;
    const char* path = "myfifo";
    if (mkfifo(path, 0666) == -1) {
        perror("mknod 1");
    }
    int fifofd,tfds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO,&fds);

    struct timeval time;
    time.tv_sec = 7;
    time.tv_usec = 0;
    
    fifofd = open(path,O_RDWR);
    tfds = select(STDIN_FILENO+1,&fds,NULL,NULL,&time);
    
    if(tfds==-1){
        PRINTSTDERROR("select() error");
        exit(EXIT_FAILURE);
    }
    else if(tfds == 0){
        printf("Time out occure\n");
        exit(EXIT_SUCCESS);
    }
    else{
        if(FD_ISSET(STDIN_FILENO,&fds)==0){
            PRINTSTDERROR("FD_ISSET() Error");
            exit(EXIT_FAILURE);
        }
        else{
            char buff[128];
            ssize_t bytes = read(STDOUT_FILENO,buff,sizeof(buff)-1);
            
            if(bytes>0)
                buff[bytes];
            
            if(write(fifofd,buff,sizeof(buff))==-1){
                PRINTSTDERROR("Error Writing");
                exit(EXIT_FAILURE);
            }
            printf("\nSuccessfully written to Fifo\nMSG: %s\n",buff);
        }
    }
    return 0;
}
/*
Output======================================================================
$ ./Q22
Hi how are you?

Successfully written to Fifo
MSG: Hi how are you?
============================================================================
*/