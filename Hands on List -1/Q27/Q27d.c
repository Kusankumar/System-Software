#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(){
    char *argv[]={"ls","-rl",NULL};
    int e = execvp("/bin/ls",);
    if(e==-1){
        fprintf(stderr,"Error occured: %s\n",strerror(errno));
        return 1;
    }
    return 0;
}
/*=============================================================
$ ./Q27c
total 60
-rw-rw-r-- 1 sonu2030 sonu2030   358 Aug 31 18:15 Q27c.c
-rwxrwxr-x 1 sonu2030 sonu2030 16200 Aug 31 18:15 Q27c
-rw-rw-r-- 1 sonu2030 sonu2030   323 Aug 31 18:11 Q27b.c
-rwxrwxr-x 1 sonu2030 sonu2030 16144 Aug 31 18:11 Q27b
-rw-rw-r-- 1 sonu2030 sonu2030   458 Aug 31 18:11 Q27a.c
-rwxrwxr-x 1 sonu2030 sonu2030 16144 Aug 31 18:08 Q27a

*/
