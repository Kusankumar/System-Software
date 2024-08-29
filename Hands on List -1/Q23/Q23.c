#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


int main(){
  pid_t cid = fork();
  
  if(cid==-1){
    fprintf(stderr, "Failed to create Child Process: %s\n", strerror(errno));
    return 1;
  }
  
  if(cid==0){
    exit(EXIT_SUCCESS);
  }
  if(cid>0){
    printf("%d",getpid());
    fflush(stdout);
    sleep(100);
  }
  return 0;
}

/*===========================================================================
Output
sonu2030@sonu152:/proc$ ps -ef | grep main
sonu2030    6337    3198  0 20:18 pts/0    00:00:00 ./main
sonu2030    6338    6337  0 20:18 pts/0    00:00:00 [main] <defunct>
sonu2030    6342    6248  0 20:19 pts/4    00:00:00 grep --color=auto main

*/
