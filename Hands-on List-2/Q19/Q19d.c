/*
============================================================================
Name : Q19d.c
Author : Sonu Kumar Mahto

Description--------------------------
19. Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    mode_t mode = 0666;

    if (mkfifo("myfifo2", mode) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }
    printf("FIFO created successfully\n");

    return 0;
}
/*
Output======================================================================
$ ./Q19d
FIFO created successfully
============================================================================
*/