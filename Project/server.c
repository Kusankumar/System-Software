#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "loginUser.c"
#define UCSIZE 64

#define BUFF_SIZE 512
void getError(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[]){
    if(argc<2){
        fprintf(stderr,"Provide Port Number");
        exit(EXIT_FAILURE);
    }

    int sockfd,newsockfd,port;
    char buff[BUFF_SIZE];
    ssize_t bytes;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t clilen;

    port = atoi(argv[1]);
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){getError("Error opening Socket");}
    bzero((char *)&seraddr,sizeof(seraddr));

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr=INADDR_ANY;
    seraddr.sin_port = htons(port);

    if(bind(sockfd,(struct sockaddr*) &seraddr,sizeof(seraddr))<0){getError("bind() Error");}

    listen(sockfd,1);
    clilen = sizeof(cliaddr);

    newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
    if(newsockfd<0) getError("Error accepting connection");

    write(newsockfd,"Successfully connected\n",sizeof("Successfully connected\n"));

    int act,loginAct;
    char userTypeMsg[] = "Select User Type:\n1. Customer\n2. Employee\n3. Admin\n4. Exit\nEnter: ";
    while (1){
        char greetMsg[]="\n-----------------------Welcome-----------------------\n1. Login\n2. Exit\nEnter your Chioce:";
        write(newsockfd,greetMsg,strlen(greetMsg));

        //receive loginAct from client
        read(newsockfd,&loginAct,sizeof(int));

        
        //Login User
        if(loginAct==1){
            char username[UCSIZE],passwd[UCSIZE];
            bzero(buff,BUFF_SIZE);
            bzero(username,UCSIZE);
            bzero(passwd,UCSIZE);

            write(newsockfd,"Enter Username: ",strlen("Enter Username: "));
            bytes = read(newsockfd,username,sizeof(username)-1);
            username[bytes] = '\0';

            write(newsockfd,"Enter Password: ",strlen("Enter Password: "));
            bytes = read(newsockfd,passwd,sizeof(passwd)-1);
            passwd[bytes] = '\0';

            //Authemticating
            int auth = login(username,passwd);
            write(newsockfd,&auth,sizeof(int));

            if(auth<=0) break;
                
            //Sync wait
            // read(newsockfd,buff,BUFF_SIZE-1);

            if(auth>1000){
                //Welcome customer
                char customerMenu[]="1. View Account Balance\n2. Deposit Money\n3. Withdraw Money\n4. Send Money\n5. Apply for Loan\n6. View History\n7. Add Feedback\n8. Change Password\n9. Logout";
                
                
            }
            else if(auth>200 && auth<=1000){
                //welcome employee
                char employeeMenu[]="1. Add New User\n2. Modify Customer\n3. Process Loan Application\n4. View assigned Loan\n5. change password\n6. Logout\nEnter choice: ";

            }
            else if(auth>50 && auth<=200){
                //Welcome manager
                char managerMenu[]="1. Activate Customer\n2.Deactivate Customer\n3. ALA to Employee\n4. Review Customer Feedback\n5. Logout\nEnter your choice: ";

            }
            else if(auth>=1 && auth<=50){
                //welcome admin
                char adminMenu[]="1. Modify Employee\n2. Modify Customer\n3. Add Employee\n4. Manage Roles5. change password\n6. Logout\nEnter Choice: ";
                write(newsockfd,adminMenu,strlen(adminMenu));
                
                read(newsockfd,buff,sizeof(buff)-1);
            }

        }
        else if(loginAct==2){
            
            break;
        }        
    }
    close(newsockfd);
    close(sockfd);

    return 0;
}