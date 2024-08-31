#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(){
    int e = execlp("ls","ls","-rl",(char *)NULL);
    if(e==-1){
        fprintf(stderr,"Error occured: %s\n",strerror(errno));
        return 1;
    }
    return 0;
}
/*=============================================================

*/
