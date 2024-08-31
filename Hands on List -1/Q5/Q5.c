/*
============================================================================
Name : Q5.c
Author : Sonu Kumar Mahto

Description--------------------------
5. Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd

Date: 30th Aug, 2024.
============================================================================*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

bool isfdvalid(int fd){
  if(fd==-1){
    perror("Something is wrong");
    return false;
  }
  return true;
}

int main(void){
  const char *filenames[5] = {"f1.c","f2.c","f3.c","f4.c","f5.c"};
  char loopCode[200];
  
  int codefd = open("codesnippet.c",O_RDONLY);
  if (!isfdvalid(codefd))
    return 1;
  
  char buffer[512];
  ssize_t readline;
  
  for(int i=0;i<5;++i){
    int fd = creat(filenames[i],0666);
    if (!isfdvalid(fd)){
      close(codefd);
      return 1;
    }
    
    lseek(codefd,0,SEEK_SET);
    while((readline = read(codefd,buffer,sizeof(buffer)))>0){
      ssize_t data = write(fd,buffer,readline);
      if(!isfdvalid(data)){
      close(fd);
      close(codefd);
      return 1;
      }
    }
    close(fd);  
  }
  close(codefd);
  return 0;
}

/*
File descriptor table at /proc/pid/fd-------------------------------------------------
f1.c
sonu2030@sonu152:/proc/37275$ cd fd
sonu2030@sonu152:/proc/37275/fd$ la
0  1  2

f2.c
sonu2030@sonu152:/proc/37275/fd$ cd /proc/37276/fd
sonu2030@sonu152:/proc/37276/fd$ ls
0  1  2

f3.c
sonu2030@sonu152:/proc/37276/fd$ cd /proc/37277/fd
sonu2030@sonu152:/proc/37277/fd$ ls
0  1  2

f4.c
sonu2030@sonu152:/proc/37279/fd$ cd /proc/37278/fd
sonu2030@sonu152:/proc/37278/fd$ ls
0  1  2

f5.c
sonu2030@sonu152:/proc/37278/fd$ cd /proc/37279/fd
sonu2030@sonu152:/proc/37279/fd$ ls
0  1  2

*/
