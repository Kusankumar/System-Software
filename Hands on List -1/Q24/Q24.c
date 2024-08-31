#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>


int main(){
  pid_t cid = fork();
  
  if(cid==-1){
    fprintf(stderr, "Failed to create Child Process: %s\n", strerror(errno));
    return 1;
  }
  
  if(cid==0){
    sleep(10);
    printf("Parent ProcessID after Orphan: %d\n",getppid());
    fflush(stdout);
    
  }
  if(cid>0){
    printf("Parent ProcessID before Orphan: %d\n",getpid());
    fflush(stdout);
    exit(EXIT_SUCCESS);
  }
  return 0;
}

/*===========================================================================
Output
$ ./main
Parent ProcessID before Orphan: 8006
$ Parent ProcessID after Orphan: 1451

*/
