/*
============================================================================
Name : Q32a.c
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
    const char* path = "ticket.txt";
    int fd = open(path,O_RDWR | O_CREAT | O_TRUNC,0666);

    sem_t *semp = sem_open("/fsem",O_CREAT,0666,0);
    if(semp == SEM_FAILED){
        perror("sem_open() Error ");
        exit(EXIT_FAILURE);
    }

    pid_t c = fork();
    if(c==0){
        sleep(5);
        char buff[] = "94675883";
        write(fd,buff,sizeof(buff)-1);
        close(fd);
        sem_post(semp);
        exit(EXIT_SUCCESS);
    }
    else{
        close(fd);

        sem_wait(semp);
        fd = open(path,O_RDONLY);
        
        char buff[10];
        ssize_t bytes = read(fd,buff,sizeof(buff));
        if (bytes>0){
            buff[bytes] = '\0';
        }
        printf("Ticket Number: %d\n",atoi(buff));
        wait(NULL);
        sem_unlink("/fsem");
        close(fd);
    }
    return 0;
}
/*
Output======================================================================
$ ./Q32a
94675883
============================================================================
*/