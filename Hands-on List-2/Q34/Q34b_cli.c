/*
============================================================================
Name : Q34b_cli.c
Author : Sonu Kumar Mahto

Description--------------------------
34. Write a program to create a concurrent server.
a. use fork
b. use pthread_create

Date: 15 Sept, 2024
============================================================================
*/
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main(){
    struct sockaddr_in serv;

    int sd;
    char buff[50];
    sd = socket(AF_UNIX, SOCK_STREAM, 0);

    serv.sin_family = AF_UNIX;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5055);

    connect(sd, (void*) (&serv), sizeof(serv));
    write(sd, "Hello Server\n", 14);
    read(sd, buff, sizeof(buff));
    printf("Message from Server: %s\n", buff);
    return 0;
}
/*
Output======================================================================

============================================================================
*/