/*
============================================================================
Name : Q24.c
Author : Sonu Kumar Mahto

Description--------------------------
24. Write a program to create a message queue and print the key and message queue id.

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    key = ftok(".", 83);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*
Output======================================================================
$ ./Q24.c
Message Queue Key: 1392844171
Message Queue ID: 3
============================================================================
*/