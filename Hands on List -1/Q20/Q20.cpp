/*=====================================================================
Name: Sonu Kumar Mahto
Roll: MT2024152


*/

#include<iostream>
#include <unistd.h>
#include <sys/resource.h>
#include<cerrno>
#include<cstring>

int main(){
  pid_t pid = getpid();
  errno =0;
  int p = getpriority(PRIO_PROCESS,pid);
  
  if(errno==-1){
    std::cout << "Failed to get Priority:" << std::strerror(errno) << std::endl;
    return 1;
  }
  std::cout << "Priority of the Process: " << p <<std::endl;
  
  errno = 0;
  nice(5);
  if(errno!=0){
    std::cout << "Failed to get Priority:" << std::strerror(errno) << std::endl;
    return 1;
  }
  
  p = getpriority(PRIO_PROCESS,pid);
  std::cout << "Updated Priority of the Process: " << p <<std::endl;
  return 0;
}

/*
==============================================================
Ouput: 
$ ./main
Priority of the Process: 0
Updated Priority of the Process: 5

*/
