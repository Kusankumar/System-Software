#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<cstring>
#include<ctime>
#include<fcntl.h>

bool isfdvalid(int fd){
  if(fd<0){
    perror("Error Occure");
    return false;
  }
  return true;
}
int main(){
  
  const char *path = "testfile.txt";
  
  int fd = open(path, O_RDWR | O_CREAT, 0666);
  if(!isfdvalid(fd)){
    close(fd);
    return 1;
  }
  
  char buffer[10];
  //Writing 1st 10byte
  if(read(STDIN_FILENO,buffer,sizeof(buffer))<0){
    close(fd);
    return 1;
  }
  if(write(fd,buffer,sizeof(buffer))<0){
    close(fd);
    return 1;
  }
  
  off_t offset = lseek(fd,10,SEEK_CUR);
  if(offset == (off_t)-1){
    close(fd);
    return 1;
  }
  
  //Writing 2nd 10byte
  if(read(STDIN_FILENO,buffer,sizeof(buffer))<0){
    close(fd);
    return 1;
  }
  if(write(fd,buffer,sizeof(buffer))<0){
    close(fd);
    return 1;
  }
  std::cout << "Return value of lseek() : " << offset << std::endl;
  close(fd);
  return 0;
}
/*
a. check the return value of lseek------------------------------------------------------
sonu2030@sonu152:~/Desktop/IIITB WorkSpace/1st Sem/System Software/Lab/Hands on List -1/Q10$ ./main
I'm Sonu
What's up? 
Return value of lseek() : 20

b. open the file with od and check the empty spaces in between the data-----------------
$ od -c testfile.txt
0000000   I   '   m       S   o   n   u  \n  \0  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   W   h   a   t   '   s       u   p   ?
0000036

*/
