/*
============================================================================
Name : Q32c.c
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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char *file1 = "test1.txt";
    const char *file2 = "test2.txt";

    int fd1 = open(file1, O_RDWR);
    int fd2 = open(file2, O_RDWR);

    if (fd1 == -1 || fd2 == -1) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    sem_t *semp = sem_open("/counting_sem", O_CREAT, 0666, 2);
    if (semp == SEM_FAILED) {
        perror("sem_open() Error");
        exit(EXIT_FAILURE);
    }

    sem_wait(semp);
    sem_wait(semp);
    pid_t c = fork();
    if (c == 0) {
        sleep(2);
        char buff1[32], buff2[32];
        ssize_t bytes1, bytes2;

    
        bytes1 = read(fd1, buff1, sizeof(buff1));
        if (bytes1 > 0) buff1[bytes1] = '\0';

        bytes2 = read(fd2, buff2, sizeof(buff2));
        if (bytes2 > 0) buff2[bytes2] = '\0';

        printf("%s, %s",buff1,buff2);

        close(fd1);
        close(fd2);

        sem_post(semp);
        sem_post(semp);

        exit(EXIT_SUCCESS);
    } else {
        sem_wait(semp);
        sem_wait(semp);

        fd1 = open(file1, O_RDWR | O_TRUNC);
        fd2 = open(file2, O_RDWR | O_TRUNC);

        char buff1[] = "This is written by Parent";
        char buff2[] = "This is written by Parent";

        lseek(fd1, 0, SEEK_SET);
        write(fd1, buff1, strlen(buff1));

        lseek(fd2, 0, SEEK_SET);
        write(fd2, buff2, strlen(buff2));

        close(fd1);
        close(fd2);

        wait(NULL);

        sem_unlink("/counting_sem");
    }

    return 0;
}
/*
Output======================================================================
Before:
test1.txt
Sonu Kumar Mahto

test2.txt
student at IIIT B
--------------------------------------
After:
test1.txt
This is written by Parent

test2.txt
This is written by Parent
============================================================================
*/
