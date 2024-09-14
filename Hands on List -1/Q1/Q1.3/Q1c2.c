#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(void) {
    char *fifopath = "myfifo";
    if (mkfifo(fifopath, 0666) == -1) {
        perror("mkfifo: ");
    }
    char user1[100], user2[100];
    while (1) {
        int file = open(fifopath, O_RDONLY);
        read(file, user1, 100);
        printf("From User 1: %s\n", user1);
        close(file);
        
        file = open(fifopath, O_WRONLY);
        printf("Type here: ");
        fgets(user2, 100, stdin);
        write(file, user2, strlen(user2) + 1);
        close(file);    
    }
    return 0;
}

