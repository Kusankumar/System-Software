/*
============================================================================
Name : Q21.c
Author : Sonu Kumar Mahto

Description--------------------------
21. Write a program, call fork and print the parent and child process id.

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(){
        pid_t cid = fork();
	if(cid==-1){
	        fprintf(stderr,"Some problem occur: %s \n",strerror(errno));
		return 1;
	}
	else if(cid == 0){
	        printf("Parent ProcessID: %d \nChild ProcessID: %d\n",getppid(),getpid());
	}
	if(cid!=0)
	        printf("Parent ProcessID: %d \nChild ProcessID: %d\n",getpid(),cid);
	return 0;
}

