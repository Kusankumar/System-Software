/*
============================================================================
Name : Q20.c
Author : Sonu Kumar Mahto

Description--------------------------
20. Find out the priority of your running program. Modify the priority with nice command

Date: 30th Aug, 2024.
============================================================================*/

#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>
#include<errno.h>
#include<string.h>

int main(){
  pid_t pid = getpid();
  errno =0;
  int p = getpriority(PRIO_PROCESS,pid);
  
  if(errno==-1){
    fprintf(stderr,"Failed to get Priority: %s\n",strerror(errno));
    return 1;
  }
  printf("Priority of the Process: %d\n",p);
  
  errno = 0;
  nice(5);
  if(errno!=0){
    fprintf(stderr,"Failed to get Priority: %s\n",strerror(errno));
    return 1;
  }
  
  p = getpriority(PRIO_PROCESS,pid);
  printf("Updated Priority of the Process: %d\n",p);
  return 0;
}

/*
==============================================================
Ouput: 
$ ./main
Priority of the Process: 0
Updated Priority of the Process: 5

*/
