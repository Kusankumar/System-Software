/*
============================================================================
Name : Q27a.c
Author : Sonu Kumar Mahto

Description--------------------------
27. Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#define MSGSIZE 128

struct msgbuf{
    long mtype;
    char mtext[MSGSIZE];
};

int main(){
    key_t key;
    int msgid;
    ssize_t bytes;
    struct msqid_ds mqstat;
    struct msgbuf msg1,msg2;

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
    
    msg1.mtype = 1;
    //Writing in the queue
    bytes = read(STDIN_FILENO,msg1.mtext,sizeof(msg1.mtext)-1);
    if(bytes>0)
        msg1.mtext[bytes]='\0';
    msgsnd(msgid,&msg1,bytes,0);
    sleep(1);
    
    //Retirving from the queue
    msgrcv(msgid, &msg2, sizeof(msg2.mtext), 1, 0);
    printf("Received message: %s\n", msg2.mtext);
    
    return 0;
}
/*
Output======================================================================
$ ipcs -q
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x53051de0 5          sonu2030   666        40           5           
0x53051e28 6          sonu2030   666        14           1   

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x53051de0 5          sonu2030   666        40           5           
0x53051e28 6          sonu2030   666        0            0   
============================================================================
*/

