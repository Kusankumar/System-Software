#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
extern char **environ;

int main(){
  int e = execl("hello","./hello",(char *)NULL);
  if(e==-1){
    fprintf(stderr,"Error Occure: %s\n",strerror(errno));
    return 1;
  }
  printf("This should not be printed\n");
  return 0;
}
