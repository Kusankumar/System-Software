#include<iostream>
#include<unistd.h>
#include<x86intrin.h>

uint64_t getTsc(){return _rdtsc();}

int main(){
  uint64_t st=getTsc();
  pid_t pid = getpid();
  uint64_t et=getTsc();
  std::cout << "Time to Execute getpid() system call " << (et-st) << std::endl;
  return 0;
}
