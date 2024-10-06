/*
============================================================================
Name : Q34b_ser.c
Author : Sonu Kumar Mahto

Description--------------------------
34. Write a program to create a concurrent server.
a. use fork
b. use pthread_create

Date: 15 Sept, 2024
============================================================================
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

void *handle_client(void *socket_desc) {
    int new_socket = (int)socket_desc;
    free(socket_desc); 
    char buffer[50] = {0};

    int bytes_read = read(new_socket, buffer, 50);
    if (bytes_read > 0) {
        printf("Client: %s\n", buffer);
        send(new_socket, "Message received", strlen("Message received"), 0);
    }
    close(new_socket); 
    pthread_exit(NULL); 
}

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

    // while(1){

    //     nsd = accept(sd, (void*)(&cli), &sz);
    //     pthread_t thread_id;
    //     int *new_sock = malloc(sizeof(int));
    //     *new_sock = nsd;

    //     if (pthread_create(&thread_id, NULL, handle_client, (void*)new_sock) != 0) {
    //         perror("Thread creation failed");
    //         free(new_sock);
    //         close(nsd);
    //     }

    //     pthread_detach(thread_id);
    // }
}
/*
Output======================================================================

============================================================================
*/