/*
============================================================================
Name : Q27d.c
Author : Sonu Kumar Mahto

Description--------------------------
27. Write a program to execute ls -Rl by the following system calls
a. execl
b. execlp
c. execle

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(){
    char *argv[]={"ls","-rl",NULL};
    int e = execv("/bin/ls",argv);
    if(e==-1){
        fprintf(stderr,"Error occured: %s\n",strerror(errno));
        return 1;
    }
    return 0;
}
/*=============================================================
$ ./Q27d
total 80
-rw-rw-r-- 1 sonu2030 sonu2030   698 Aug 31 18:24 Q27d.c
-rwxrwxr-x 1 sonu2030 sonu2030 16200 Aug 31 18:25 Q27d
-rw-rw-r-- 1 sonu2030 sonu2030   712 Aug 31 18:15 Q27c.c
-rwxrwxr-x 1 sonu2030 sonu2030 16200 Aug 31 18:15 Q27c
-rw-rw-r-- 1 sonu2030 sonu2030   323 Aug 31 18:11 Q27b.c
-rwxrwxr-x 1 sonu2030 sonu2030 16144 Aug 31 18:11 Q27b
-rw-rw-r-- 1 sonu2030 sonu2030   458 Aug 31 18:11 Q27a.c
-rwxrwxr-x 1 sonu2030 sonu2030 16144 Aug 31 18:08 Q27a

*/
