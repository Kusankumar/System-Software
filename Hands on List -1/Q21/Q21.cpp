/*
============================================================================
Name : Q21.c
Author : Sonu Kumar Mahto

Description--------------------------
21. Write a program, call fork and print the parent and child process id.

Date: 30th Aug, 2024.
============================================================================*/
#include<iostream>
#include<unistd.h>
#include<cstring>
#include<cerrno>

int main(){
        pid_t cid = fork();
	if(cid==-1){
		std::cout << "Some problem occur: " << std::strerror(errno) << std::endl;
		return 1;
	}
	else if(cid == 0){
		std::cout << "Parent ProcessID: " << getppid() << "  Child ProcessID: " << getpid() << std::endl;
	}
	if(cid!=0)
                std::cout << "Parent ProcessID: " << getpid() << "  Child ProcessID: " << cid << std::endl;
	return 0;
}

