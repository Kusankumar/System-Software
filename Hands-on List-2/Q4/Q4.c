/*
============================================================================
Name : Q4.c
Author : Sonu Kumar Mahto

Description--------------------------
4. Write a program to measure how much time is taken to execute 100 getppid() system call. Use time stamp counter.

Date: 12 Sept, 2024
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<x86intrin.h>

int64_t getTsc(){_rdtsc();}

int64_t main(){

    int64_t start = getTsc();
    for(int i=0;i<100;i++){getppid();}
    int64_t end = getTsc();

    printf("Time Required: %jd\n",(int64_t)(end-start));

    return 0;
}
/*
Output======================================================================
$ ./Q4
Time Required: 75766
============================================================================
*/