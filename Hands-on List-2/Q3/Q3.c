/*
============================================================================
Name : Q3.c
Author : Sonu Kumar Mahto

Description--------------------------
3. Write a program to set (any one) system resource limit. Use setrlimit system call.

Date: 12 Sept, 2024
============================================================================
*/
#define _GNU_SOURCE
#define _FILE_OFFSET_BITS 64
#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    pid_t          pid;
    struct rlimit  old, new;
    struct rlimit  *newp;

    if (!(argc == 2 || argc == 4)) {
        fprintf(stderr, "\nUsage: %s <pid> [<new-soft-limit> ""<new-hard-limit>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = atoi(argv[1]);
    newp = NULL;
    if (argc == 4) {
        new.rlim_cur = atoi(argv[2]);
        new.rlim_max = atoi(argv[3]);
        newp = &new;
    }
    if (prlimit(pid, RLIMIT_STACK, newp, &old) == -1)
        err(EXIT_FAILURE, "prlimit-1");
    printf("\nPrevious limits: \nSoft=%jd Hard=%jd\n",(intmax_t) old.rlim_cur, (intmax_t) old.rlim_max);

    if (prlimit(pid, RLIMIT_STACK, NULL, &old) == -1)
        err(EXIT_FAILURE, "prlimit-2");
    printf("\nNew limits: \nSoft=%jd Hard=%jd\n",(intmax_t) old.rlim_cur, (intmax_t) old.rlim_max);

    return 0;
}

/*
int main(int argc, char * argv[]){
    if(!(argc==2 || argc==4)){
        fprintf(stderr, "\nInput Format: \n%s <pid> <new-soft-limit> <new-hard-limit>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t          pid;
    struct rlimit  old, new;

    pid = atoi(argv[1]) ;
    if(argc == 4){
        new.rlim_cur = atoi(argv[2]);
        new.rlim_max = atoi(argv[3]);
    }

    if(getrlimit(RLIMIT_STACK,&old)==-1){
        fprintf(stderr,"Error Getting Resource Information: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("\nPrevious Resource Information\nSoft: %jd  Hard: %jd\n",(intmax_t) old.rlim_cur,(intmax_t) old.rlim_max);

    if(setrlimit(RLIMIT_STACK,&new)==-1){
        fprintf(stderr,"Error Getting Resource Information: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("\nNew Resource Information\nSoft: %jd  Hard: %jd\n",(intmax_t) new.rlim_cur,(intmax_t) new.rlim_max);
    return 0;
}
*/
/*
Output======================================================================
$ ./Q3 0 10 100
Previous limits: 
Soft=8388608 Hard=-1

New limits: 
Soft=10 Hard=100
============================================================================
*/