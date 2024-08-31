#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(){
    int e = execl("/bin/ls","ls","-rl",(char *)NULL);
    if(e==-1){
        fprintf(stderr,"Error occured: %s\n",strerror(errno));
        return 1;
    }
    return 0;
}

/*=============================================================
$ ./Q27a
total 20
-rw-rw-r-- 1 sonu2030 sonu2030   258 Aug 31 18:08 Q27a.c
-rwxrwxr-x 1 sonu2030 sonu2030 16144 Aug 31 18:08 Q27a

*/
