/*
============================================================================
Name : Q2.c
Author : Sonu Kumar Mahto

Description--------------------------
3. Write a program to create a file and print the file descriptor value. Use creat ( ) system call

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(void){
	char *path = "testfile.txt";
	int fd = creat(path,0666);

	if(fd==-1){
		perror("File creation failed: ");
		return 1;
	}
	char data[100];
	fgets(data, 100, stdin);
	ssize_t wfd = write(fd,data,strlen(data));
	if(wfd<0){
		perror("can't write: ");
		return -1;
	}
	printf("FileDescriptor: %d\nFile written successfully \n",fd);
	close(fd);
	return 0;
}
/*===========================================================================
$ gcc Q3.c -o main

$ ./main
hi what's up 
FileDescriptor: 3
File written successfully
*/
