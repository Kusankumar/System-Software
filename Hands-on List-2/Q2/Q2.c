/*
============================================================================
Name : Q2.c
Author : Sonu Kumar Mahto

Description--------------------------
2. Write a program to print the system resource limits. Use getrlimit system call.

Date: 12 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>

void getreslimit(int restype){
    struct rlimit rl;
    if(getrlimit(restype,&rl)==-1){
        fprintf(stderr,"Error Getting Resource Information: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    if(restype==RLIMIT_AS){
        printf("\nVirtual Memory:\nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_CORE){
        printf("\nCore File:\nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_CPU){
        printf("\nCPU time\nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_DATA){
        printf("\nProcess's Data segment\nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_FSIZE){
        printf("\nNew File Size\nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_LOCKS){
        printf("\nNumber of FIle lock: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_MEMLOCK){
        printf("\nBytes of Memory locked: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_MSGQUEUE){
        printf("\nPOSIX Message Queue Size \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_NICE){
        printf("\nProcess's Nice Value Limit: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_NOFILE){
        printf("\nFile Descriptor that can be Opend by the Process: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_NPROC){
        printf("\nNumber of Process can be created: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_RSS){
        printf("\nAmount of Memory Process can Use: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_RTPRIO){
        printf("\nMaximum Real-Time Priority Process can obtain: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_RTTIME){
        printf("\nCPU time limit without being Preempted: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_SIGPENDING){
        printf("\nPending Signal can be Queued \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }else if(restype==RLIMIT_STACK){
        printf("\nSize of Process Stack: \nSoft Limit: %lu\nHard Limit: %lu",rl.rlim_cur,rl.rlim_max);
    }
    return; 
}

int main(){
    for(int i=0;i<=15;++i)
        getreslimit(i);
    return 0;
}
/*
Output======================================================================
$ ./a.out
CPU time
Soft Limit: 18446744073709551615
Hard Limit: 18446744073709551615
New File Size
Soft Limit: 18446744073709551615
Hard Limit: 18446744073709551615
Process's Data segment
Soft Limit: 18446744073709551615
Hard Limit: 18446744073709551615
Size of Process Stack: 
Soft Limit: 8388608
Hard Limit: 18446744073709551615
Core File:
Soft Limit: 0
Hard Limit: 18446744073709551615
Amount of Memory Process can Use: 
Soft Limit: 18446744073709551615
Hard Limit: 18446744073709551615
Number of Process can be created: 
Soft Limit: 30018
Hard Limit: 30018
File Descriptor that can be Opend by the Process: 
Soft Limit: 1048576
Hard Limit: 1048576
Bytes of Memory locked: 
Soft Limit: 993239040
Hard Limit: 993239040
Virtual Memory:
Soft Limit: 18446744073709551615
Hard Limit: 18446744073709551615
Number of FIle lock: 
Soft Limit: 18446744073709551615
Hard Limit: 18446744073709551615
Pending Signal can be Queued 
Soft Limit: 30018
Hard Limit: 30018
POSIX Message Queue Size 
Soft Limit: 819200
Hard Limit: 819200
Process's Nice Value Limit: 
Soft Limit: 0
Hard Limit: 0
Maximum Real-Time Priority Process can obtain: 
Soft Limit: 0
Hard Limit: 0
CPU time limit without being Preempted: 
Soft Limit: 18446744073709551615

============================================================================
*/