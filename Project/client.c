#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFF_SIZE 512
#define UCSIZE 64

void getError(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[]){
    if(argc<3){
        fprintf(stderr,"Usage: %s <hotname> <port>",argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd,port;
    char buff[BUFF_SIZE];
    ssize_t bytes;
    socklen_t clilen;
    struct sockaddr_in seraddr;
    struct hostent *server;

    port = atoi(argv[2]);
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){getError("Error opening Socket");}

    server = gethostbyname(argv[1]);
    if(server==NULL) fprintf(stderr,"Invalid host");

    bzero((char *)&seraddr,sizeof(seraddr));

    seraddr.sin_family = AF_INET;
    bcopy((char*)server->h_addr_list[0],(char*)&seraddr.sin_addr.s_addr,server->h_length);
    seraddr.sin_port = htons(port);

    if(connect(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        getError("connection Failed");
    }


    bytes = read(sockfd,buff,sizeof(buff)-1);
    printf("Server:\n%s\n",buff);

    int act,loginAct;
    while (1){
        bzero(buff,BUFF_SIZE);
        bytes = read(sockfd,buff,sizeof(buff)-1);
        buff[bytes]='\0';
        printf(" %s",buff);
        scanf("%d",&loginAct);

        //Login Action
        write(sockfd,&loginAct,sizeof(int));
        

        //Login User
        if(loginAct==1){
            char username[UCSIZE],passwd[UCSIZE];
            int auth;
            bzero(buff,BUFF_SIZE);

            bytes = read(sockfd,buff,sizeof(buff)-1);
            buff[bytes]='\0';
            printf("%s",buff);
            scanf("%s",username);
            write(sockfd,username,strlen(username));

            bzero(buff,BUFF_SIZE);
            bytes = read(sockfd,buff,sizeof(buff)-1);
            buff[bytes]='\0';
            printf("%s",buff);
            scanf("%s",passwd);
            write(sockfd,passwd,strlen(passwd));

            //Authenticating
            bzero(buff,BUFF_SIZE);
            bytes = read(sockfd,&auth,sizeof(int));
            if(auth<=0) break;

            //Sync write
            if(auth>1000){
                //Welcome customer
                printf("\n-------------------Welcome-------------------\n");
                
            }
            else if(auth>200 && auth<=1000){
                //welcome employee
            }
            else if(auth>50 && auth<=200){
                //Welcome manager
            }
            else if(auth>=1 && auth<=50){
                //welcome admin
                read(sockfd,buff,sizeof(buff)-1);

                write(sockfd,"Sync",strlen("Sync"));
            }

        }
        else if(loginAct==2){
            break;
        }
    }
    close(sockfd);

    return 0;
}