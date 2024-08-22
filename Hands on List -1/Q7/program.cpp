#include<iostream>
#include<unistd.h>
#include<cerrno>
#include<cstring>
#include<fcntl.h>

bool isfdvalid(int fd){
  if(fd<0){
    perror("Something is wrong");
    return false;
  }
  return true;
}

int main(void){
  const char *source = "testfile.txt";
  const char *dest = "test.txt";
  
  int sfd = open(source,O_RDONLY);
  if(!isfdvalid(sfd)){
    close(sfd);
    return 1;
  }
  
  int dfd = open(dest,O_WRONLY | O_CREAT | O_TRUNC,0666 );
  if(!isfdvalid(dfd)){
    close(dfd);
    return 1;
  }
  
  char buffer[512];
  ssize_t readline;
  
  while((readline = read(sfd,buffer,sizeof(buffer)))>0){
    ssize_t writeline = write(dfd,buffer,readline);
    if(readline!=writeline){
      perror("Something is wrong");
      close(sfd);
      close(dfd);
      return 1;
    }
  }
  if(!isfdvalid(readline)){
    close(sfd);
    close(dfd);
    return 1;
  }
  
  close(sfd);
  close(dfd);
  return 0;
}

