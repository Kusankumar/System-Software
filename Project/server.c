//Multi client-server chat
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

#include "serverComponent.c"
#include "serverModules.c"

#define PORT 9898
#define BUFF_SIZE 1024
#define BACKLOG 10
#define UCSIZE 64

void getError(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
void init_semaphore(int semid, int semnum, int init_value) {
    union semun sem_union;
    sem_union.val = init_value;
    if (semctl(semid, semnum, SETVAL, sem_union) == -1) {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }
}

int clientHandler(int sockfd,int *semid){
    int act,loginAct;
    char buff[BUFF_SIZE];
    ssize_t bytes;
    
    while (1){
        //receive loginAct from client
        read(sockfd,&loginAct,sizeof(int));

        //Login User
        if(loginAct==1){
            char username[UCSIZE],passwd[UCSIZE];
            bzero(buff,BUFF_SIZE);
            bzero(username,UCSIZE);
            bzero(passwd,UCSIZE);

            //Getting Username
            write(sockfd,"Enter Username: ",strlen("Enter Username: "));
            bytes = read(sockfd,username,sizeof(username)-1);
            username[bytes] = '\0';

            //Getting Password
            write(sockfd,"Enter Password: ",strlen("Enter Password: "));
            bytes = read(sockfd,passwd,sizeof(passwd)-1);
            passwd[bytes] = '\0';

            //Authemticating
            int auth = login(username,passwd);
            write(sockfd,&auth,sizeof(int));

            //Sync wait
            read(sockfd,buff,BUFF_SIZE-1);
            if(auth<0){
                printf("No User in Database\n");
            }
            if(auth==0){
                printf("Deactive account\n");
            }
            
            int usession = checkUserSession(auth);
            write(sockfd,&usession,sizeof(int));
            read(sockfd,buff,BUFF_SIZE-1);
            if(usession==1){
                write(sockfd,"User has active session. Please close the previous session\n",strlen("User has active session. Please close the previous session\n"));
                continue;
            }

            if(auth>1000){
                //customer Zone
                modifyUserSession(auth,1);
                int cutomerExitStatus = customerZone(sockfd,auth,semid);
                modifyUserSession(auth,0);
                if(cutomerExitStatus!=1) fprintf(stderr,"Client Module Terminated unexpectedly\n");
            }
            else if(auth>200 && auth<=1000){
                //welcome employee
                modifyUserSession(auth,1);
                int employeeExitStatus = employeeZone(sockfd,auth,semid);
                modifyUserSession(auth,0);
                if(employeeExitStatus!=1) fprintf(stderr,"Employee Module Terminated unexpectedly\n");
            }
            else if(auth>50 && auth<=200){
                //Welcome manager
                modifyUserSession(auth,1);
                int managerExitStatus = managerZone(sockfd,auth,semid);
                modifyUserSession(auth,0);
                if(managerExitStatus!=1) fprintf(stderr,"Manager Module Terminated unexpectedly\n");
            }
            else if(auth>=1 && auth<=50){
                //welcome admin
                modifyUserSession(auth,1);
                int adminExitStatus = administratorZone(sockfd,auth,semid);
                modifyUserSession(auth,0);
                if(adminExitStatus!=1) fprintf(stderr,"Client Module Terminated unexpectedly\n");
            }
        }
        else if(loginAct==2){
            break;
        }        
    }
    return 0;
}

int main(){
    int sockfd,newsockfd;
    char buff[BUFF_SIZE];
    pid_t cpid;
    ssize_t bytes;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t clilen;
    int locks=10;

    sem_t *semp = sem_open("/fsem",O_CREAT,0666,1);
    if(semp == SEM_FAILED){
        perror("sem_open() Error ");
        exit(EXIT_FAILURE);
    }

    //Locking
    key_t key = ftok(".", 'M');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    int semid = semget(key, locks, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < 10; i++){ init_semaphore(semid, i, 1);}

    //socket connection
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){getError("Error opening Socket");}
    bzero((char *)&seraddr,sizeof(seraddr));

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORT);

    if(bind(sockfd,(struct sockaddr*) &seraddr,sizeof(seraddr))<0){getError("bind() Error");}

    listen(sockfd,BACKLOG);
    clilen = sizeof(cliaddr);
    printf("Listening...\n");

    while(1){
        newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
        if(newsockfd<0) getError("Error accepting connection");
        printf("Connection Accepted with fd:%d\nSocket %s:%d\n",newsockfd,inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
        cpid=fork();
        if(cpid<0) getError("Error Handling new connection");
        if(cpid==0){
            close(sockfd);
            if(clientHandler(newsockfd,&semid)==0)
                printf("Client disconnected\nSocket %s:%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
            else
                printf("Connection Exit unexpectedly\nSocket %s:%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
            exit(0);
        }
        
    }
    close(newsockfd);
    close(sockfd);

    return 0;
}