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
        int file = open(fifopath, O_WRONLY);
        printf("Type here: ");
        fgets(user2, 100, stdin);
        write(file, user2, strlen(user2) + 1);
        close(file);

        file = open(fifopath, O_RDONLY);
        read(file, user1, sizeof(user1));
        printf("From User 2: %s\n", user1);
        close(file);
    }
    return 0;
}

/*=============================================================
$ gcc Q1c1.c -o main1
Q1.3$ ./main2
mkfifo: : File exists
From User 1: hi

Type here: holla
From User 1: yo

Type here: ^C

$ gcc Q1c2.c -o main2
./main1
mkfifo: : File exists
Type here: hi
From User 2: holla

Type here: yo
*/
