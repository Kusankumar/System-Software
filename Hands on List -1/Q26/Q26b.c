#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
extern char **environ;


int main(){
  char *arr[]={"./testfile","Sonu Kumar Mahto","SS Exam",NULL};
  
  if(execvp("./testfile",arr)==-1){
    fprintf(stderr,"Error Occured: %s\n",strerror(errno));
    return 1;
  }
  printf("This line shouldn't be printed");
  return 0;
}
/*===============================================================
$ ./Q27
Hi, My name is Sonu Kumar Mahto
Tommorow is my SS Exam
*/