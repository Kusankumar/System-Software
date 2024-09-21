/*
============================================================================
Name : Q25.c
Author : Sonu Kumar Mahto

Description--------------------------
25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv

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

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    msgctl(msgid,IPC_STAT,&mqstat);
    printf("Access Permission: %d\n",mqstat.msg_perm.mode);
    printf("UID of Owner: %d\nUID of creator: %d\n",mqstat.msg_perm.uid,mqstat.msg_perm.cuid);
    printf("GID of Owner: %d\nGID of creator: %d\n",mqstat.msg_perm.gid,mqstat.msg_perm.cgid);
    printf("last message send at: %ld\n",mqstat.msg_stime);
    printf("last message received at: %ld\n",mqstat.msg_rtime);
    printf("Last change at: %ld\n",mqstat.msg_ctime);
    printf("Size of message queue: %lu\n",mqstat.__msg_cbytes);
    printf("Number of message in Queue: %ld\n",mqstat.msg_qnum);
    printf("Maximum bytes in MQueue: %ld\n",mqstat.msg_qbytes);
    printf("PID of msgsnd: %d\n",mqstat.msg_lspid);
    printf("PID of msgrcv: %d\n",mqstat.msg_lrpid);

    return 0;
}
/*
Output======================================================================
$ ./Q25
Access Permission: 438
UID of Owner: 1000
UID of creator: 1000
GID of Owner: 1000
GID of creator: 1000
last message send at: 0
last message received at: 0
Last change at: 1726869692
Size of message queue: 0
Number of message in Queue: 0
Maximum bytes in MQueue: 16384
PID of msgsnd: 0
PID of msgrcv: 0
============================================================================
*/