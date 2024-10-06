/*
============================================================================
Name : Q32b.c
Author : Sonu Kumar Mahto

Description--------------------------
32. Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>

int main(){
    const char* path = "balance.txt";
    
    int fd = open(path,O_RDWR);
    if(fd == -1){
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    sem_t *semp = sem_open("/fsem",O_CREAT,0666,0);
    if(semp == SEM_FAILED){
        perror("sem_open() Error ");
        exit(EXIT_FAILURE);
    }

    pid_t c = fork();
    if(c==0){
        sleep(2);
        char buff[16];
        ssize_t bytes = read(fd,buff,sizeof(buff));
        if(bytes>0)buff[bytes]='\0';

        int temp = atoi(buff) + 20;
        snprintf(buff,sizeof(buff),"%d",temp);

        lseek(fd, 0, SEEK_SET);
        write(fd,buff,bytes);

        close(fd);
        sem_post(semp);
        exit(EXIT_SUCCESS);
    }
    else{
        sem_wait(semp);

        close(fd);
        fd = open(path,O_RDWR);
        
        char buff[16];
        ssize_t bytes = read(fd,buff,sizeof(buff));
        if (bytes>0) buff[bytes]='\0';

        int temp = atoi(buff) + 30;
        snprintf(buff,sizeof(buff),"%d",temp);
        
        lseek(fd, 0, SEEK_SET);
        write(fd,buff,bytes);

        wait(NULL);
        sem_unlink("/fsem");
        close(fd);
    }
    return 0;
}
/*
Output======================================================================
before 100
$ ./Q32b
after  150
============================================================================
*/