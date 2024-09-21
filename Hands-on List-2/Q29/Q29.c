/*
============================================================================
Name : Q25.c
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
#include <errno.h>
int main(){
    key_t key;
    int msgid;
    struct msqid_ds mqstat;

    key = ftok(".", 83);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    
    //Specifiy which msgQueue to be deleted
    msgid = 8;

    msgctl(msgid,IPC_RMID,&mqstat);
    if(errno == EIDRM){
        perror("Error removing message queue");
        exit(EXIT_FAILURE);
    }
    printf("Message Queue(ID: %d) Deleted Successfully\n",msgid);
    
    return 0;
}
/*
Output======================================================================
$ ./Q29
----- Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x6f051d8b 0          sonu2030   666        0            0           
0x41051d8b 1          sonu2030   666        0            0           
0x32051d8b 2          sonu2030   666        0            0           
0x53051d8b 3          sonu2030   666        0            0           
0x53051dfe 4          sonu2030   666        0            0           
0x53051de0 5          sonu2030   666        0            0           
0x53051e7d 8          root       600        0            0 

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x6f051d8b 0          sonu2030   666        0            0           
0x41051d8b 1          sonu2030   666        0            0           
0x32051d8b 2          sonu2030   666        0            0           
0x53051d8b 3          sonu2030   666        0            0           
0x53051dfe 4          sonu2030   666        0            0           
0x53051de0 5          sonu2030   666        0            0  
============================================================================
*/