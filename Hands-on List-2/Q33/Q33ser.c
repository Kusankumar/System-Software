/*
============================================================================
Name : Q33ser.c
Author : Sonu Kumar Mahto

Description--------------------------
33. Write a program to communicate between two machines using socket.

Date: 15 Sept, 2024
============================================================================
*/
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main(){

    struct sockaddr_in serv, cli;

    int sd, sz, nsd;
    char buff[50];

    sd = socket(AF_UNIX, SOCK_STREAM, 0); 

    serv.sin_family = AF_UNIX;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5055); 

    bind(sd, (void *)&serv, sizeof(serv));

    listen(sd, 5);

    sz = sizeof(cli);
    nsd = accept(sd, (void*)(&cli), &sz);
    read(nsd, buff, sizeof(buff));
    printf("Message from Client: %s\n", buff);
    write(nsd, "ACK from Server\n", 17);
    return 0;
}
/*
Output======================================================================
$ ./Q33ser
Message from Client: Hello Server
============================================================================
*/