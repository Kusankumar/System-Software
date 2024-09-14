/*
============================================================================
Name : Q19.c
Author : Sonu Kumar Mahto

Description--------------------------
19. Write a program to find out time taken to execute getpid system call. Use time stamp counter.

Date: 30th Aug, 2024.
============================================================================*/

#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<x86intrin.h>

uint64_t getTsc(){return _rdtsc();}

int main(){
  uint64_t st=getTsc();
  pid_t pid = getpid();
  uint64_t et=getTsc();
  printf("Time to Execute getpid() system call %lu\n",(et-st));
  return 0;
}
