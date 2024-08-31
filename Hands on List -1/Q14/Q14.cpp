/*
============================================================================
Name : Q14.c
Author : Sonu Kumar Mahto

Description--------------------------
14 Write a program to find the type of a file.
a. Input should be taken from command line.
b. program should be able to identify any type of a file.

Date: 30th Aug, 2024.
============================================================================*/
#include<iostream>
#include<sys/stat.h>
#include<unistd.h>
#include<cstring>
#include<cerrno>
#include<fcntl.h>


int main(){
  char path[64];
  ssize_t readline;
  if((readline = read(STDIN_FILENO,path,sizeof(path)-1))<0){
    std::cerr << "Error reading Input " << strerror(errno) << std::endl;
    return 1;
  }
  if(readline>0){
    path[readline]='\0';
    if(path[readline-1]=='\n')
      path[readline-1] = '\0';
  }
  
  struct stat sb;
  if(stat(path,&sb)==-1){
    std::cerr << "Error Retrieving file Info: " << strerror(errno) << std::endl;
    return 1;
  }
  if(S_ISREG(sb.st_mode))
    std::cout << path << " is a Regular File" << std::endl;
  else if(S_ISDIR(sb.st_mode))
    std::cout << path << " is a Directory" << std::endl;
  else if(S_ISCHR(sb.st_mode))
    std::cout << path << " is a Character Device" << std::endl;
  else if(S_ISBLK(sb.st_mode))
    std::cout << path << " is a Block Device" << std::endl;
  else if(S_ISFIFO(sb.st_mode))
    std::cout << path << " is a FIFO(a named pipe)" << std::endl;
  else if(S_ISLNK(sb.st_mode))
    std::cout << path << " is a Symbolic Link" << std::endl;
  else if(S_ISSOCK(sb.st_mode))
    std::cout << path << " is a Socket" << std::endl;
  else
    std::cout << " Unknown File Type" << std::endl;
  
  return 0;
}

