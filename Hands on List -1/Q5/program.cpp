#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>

bool isfdvalid(int fd){
  if(fd==-1){
    perror("Something is wrong");
    return false;
  }
  return true;
}

int main(void){
  const char *filenames[5] = {"f1.cpp","f2.cpp","f3.cpp","f4.cpp","f5.cpp"};
  char loopCode[200];
  
  int codefd = open("codesnippet.cpp",O_RDONLY);
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
f1.cpp
sonu2030@sonu152:/proc/37275$ cd fd
sonu2030@sonu152:/proc/37275/fd$ la
0  1  2

f2.cpp
sonu2030@sonu152:/proc/37275/fd$ cd /proc/37276/fd
sonu2030@sonu152:/proc/37276/fd$ ls
0  1  2

f3.cpp
sonu2030@sonu152:/proc/37276/fd$ cd /proc/37277/fd
sonu2030@sonu152:/proc/37277/fd$ ls
0  1  2

f4.cpp
sonu2030@sonu152:/proc/37279/fd$ cd /proc/37278/fd
sonu2030@sonu152:/proc/37278/fd$ ls
0  1  2

f5.cpp
sonu2030@sonu152:/proc/37278/fd$ cd /proc/37279/fd
sonu2030@sonu152:/proc/37279/fd$ ls
0  1  2

*/
