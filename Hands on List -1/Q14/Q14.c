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
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>


int main(){
  char path[64];
  ssize_t readline;
  if((readline = read(STDIN_FILENO,path,sizeof(path)-1))<0){
    fprintf(stderr,"Error reading Input %s\n",strerror(errno));
    return 1;
  }
  if(readline>0){
    path[readline]='\0';
    if(path[readline-1]=='\n')
      path[readline-1] = '\0';
  }
  
  struct stat sb;
  if(stat(path,&sb)==-1){
    fprintf(stderr,"Error Retrieving file Info: %s\n",strerror(errno));
    return 1;
  }
  if(S_ISREG(sb.st_mode))
    printf("%s is a Regular File\n",path);
  else if(S_ISDIR(sb.st_mode))
    printf("%s is a Directory\n",path);
  else if(S_ISCHR(sb.st_mode))
    printf("%s is a Character Device\n",path);
  else if(S_ISBLK(sb.st_mode))
    printf("%s is a Block Device\n",path);
  else if(S_ISFIFO(sb.st_mode))
    printf("%s is a FIFO(a named pipe)\n",path);
  else if(S_ISLNK(sb.st_mode))
    printf("%s is a Symbolic Link\n",path);
  else if(S_ISSOCK(sb.st_mode))
    printf("%s is a Socket\n",path);
  else
    printf("Unknown Fil Type");  
  return 0;
}

