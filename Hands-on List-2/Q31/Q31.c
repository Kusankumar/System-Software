/*
============================================================================
Name : Q31.c
Author : Sonu Kumar Mahto

Description--------------------------
31. Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <errno.h>


int main() {
    int semid;
    key_t key;
    struct sembuf sem_op;

    key = ftok(".",'S');
    
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl() Error");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore created\n");
    sleep(1);

    sem_op.sem_num = 0;
    sem_op.sem_op = -1; 
    sem_op.sem_flg = 0;

    printf("Acquiring the semaphore...\n");
    sleep(1);
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop() Error");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore acquired!\n");
    sleep(1);
    
    sem_op.sem_op = 1;
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop V");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore released!\n");

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore deleted\n");
    return 0;
}

/*
Output======================================================================
$ ./Q31
Semaphore created
Acquiring the semaphore...
Semaphore acquired!
Semaphore released!
Semaphore deleted

============================================================================
*/