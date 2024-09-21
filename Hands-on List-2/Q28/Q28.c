/*
============================================================================
Name : Q28.c
Author : Sonu Kumar Mahto

Description--------------------------
28. Write a program to change the exiting message queue permission.
(use msqid_ds structure)

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key;
    int msgid;
    struct msqid_ds mqstat;

    key = ftok(".", 83);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    //Specifiy which msgQueue to be update
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    msgctl(msgid,IPC_STAT,&mqstat);
    printf("Old Access Permission: %d\n",mqstat.msg_perm.mode);

    mqstat.msg_perm.mode = 0600;
    msgctl(msgid,IPC_SET,&mqstat);
    printf("New Access Permission: %d\n",mqstat.msg_perm.mode);
    
    return 0;
}
/*
Output======================================================================
$ ./Q28
Old Access Permission: 438
New Access Permission: 384
============================================================================
*/