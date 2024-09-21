/*
============================================================================
Name : Q6.c
Author : Sonu Kumar Mahto

Description--------------------------
6. Write a simple program to create three threads.

Date: 12 Sept, 2024 
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

void *sroutine(void *arg){
    printf("\n%s Created",(char *)arg);
    return NULL;
}

int main(){
    pthread_t tid1,tid2,tid3;
    void *r1,*r2,*r3;
    
    //Creating threads
    if(pthread_create(&tid1,NULL,sroutine,"Thread 1")!=0){
        fprintf(stderr,"Error Creating Thread: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&tid2,NULL,sroutine,"Thread 2")!=0){
        fprintf(stderr,"Error Creating Thread: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&tid3,NULL,sroutine,"Thread 3")!=0){
        fprintf(stderr,"Error Creating Thread: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    //Terminating threads
    if(pthread_join(tid1,&r1)!=0){
        fprintf(stderr,"Error Joining Threads: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_join(tid2,&r2)!=0){
        fprintf(stderr,"Error Joining Threads: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_join(tid3,&r3)!=0){
        fprintf(stderr,"Error Joining Threads: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }printf("\nAll Threads Terminated\n");

    return 0;
}
/*
Output======================================================================
$ ./Q6
Thread 1 Created
Thread 2 Created
Thread 3 Created
============================================================================
*/