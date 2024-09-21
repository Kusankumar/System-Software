/*
============================================================================
Name : Q26.c
Author : Sonu Kumar Mahto

Description--------------------------
26. Write a program to send messages to the message queue. Check $ipcs -q

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
    struct msgbuf msg;

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
    printf("Key: %d MessageID: %d\n",key,msgid);
    
    msg.mtype = 1;
    bytes = read(STDIN_FILENO,msg.mtext,sizeof(msg.mtext)-1);
    if(bytes>0)
        msg.mtext[bytes]='\0';
    msgsnd(msgid,&msg,sizeof(bytes),0);
    printf("Message sent successfully\n");

    return 0;
}
/*
Output======================================================================
$ ./Q26
Key: 1392844256 MessageID: 5
Hi bro what's up?           
Message sent successfully

$ ipcs -q
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x6f051d8b 0          sonu2030   666        0            0           
0x41051d8b 1          sonu2030   666        0            0           
0x32051d8b 2          sonu2030   666        0            0           
0x53051d8b 3          sonu2030   666        0            0           
0x53051dfe 4          sonu2030   666        0            0           
0x53051de0 5          sonu2030   666        40           5
============================================================================
*/