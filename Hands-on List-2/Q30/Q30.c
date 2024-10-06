/*
============================================================================
Name : Q30.c
Author : Sonu Kumar Mahto

Description--------------------------
30. Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#define SHMSIZE 1024

int main(){
    key_t key;
    int shmid;
    char *adr;

    key = ftok(".",'A');

    shmid = shmget(key,SHMSIZE,IPC_CREAT|0666);
    adr = shmat(shmid,NULL,0);

    //a. Writing Data to shared memory
    ssize_t bytes = read(STDIN_FILENO,adr,1023);
    if(bytes>0)
        adr[bytes]='\0';
    printf("Message sent: %s\n",adr);

    //b. Overwriting content of shareMemory
    adr[0] = 'K';
    printf("Message overwritten: %s\n",adr);

    sleep(1);
    //c. Detaching
    shmdt(adr);
    //d. Removing
    shmctl(shmid,IPC_RMID,NULL);
    adr=NULL;
    printf("Shareed Memory removed\n");

    return 0;
}
/*
Output======================================================================
$ ./30.c
Hi what's up?
Message sent: Hi what's up?

Message overwritten: Ki what's up?

Shareed Memory removed
============================================================================
*/

