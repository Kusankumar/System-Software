#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define PORT 9898
#define BUFF_SIZE 1024
#define UCSIZE 64

void getError(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(){
    int sockfd;
    char buff[BUFF_SIZE];
    ssize_t bytes;
    socklen_t clilen;
    struct sockaddr_in seraddr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){getError("Error opening Socket");} 


    bzero((char *)&seraddr,sizeof(seraddr));

    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(PORT);
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        getError("connection Failed");
    }


    int act,loginAct;
    while (1){
        bzero(buff,BUFF_SIZE);
        char greetMsg[]="\n-----------------------Welcome-----------------------\n1. Login\n2. Exit\nEnter Chioce: ";
        printf("%s",greetMsg);
        scanf("%d",&loginAct);

        //Login Action
        write(sockfd,&loginAct,sizeof(int));
        

        //Login User
        if(loginAct==1){
            char username[UCSIZE],passwd[UCSIZE];
            int auth;
            bzero(buff,BUFF_SIZE);

            //Enter Username
            bytes = read(sockfd,buff,sizeof(buff)-1);
            buff[bytes]='\0';
            printf("%s",buff);
            scanf("%s",username);
            write(sockfd,username,strlen(username));

            //Enter Password
            bzero(buff,BUFF_SIZE);
            bytes = read(sockfd,buff,sizeof(buff)-1);
            buff[bytes]='\0';
            printf("%s",buff);
            scanf("%s",passwd);
            write(sockfd,passwd,strlen(passwd));

            //Authenticating
            bzero(buff,BUFF_SIZE);
            bytes = read(sockfd,&auth,sizeof(int));

            //Sync write
            write(sockfd,"Sync",strlen("Sync"));
            if(auth<=0){
                printf("Error at auth");
                break;
            }
            
            if(auth>1000){
                //Welcome customer
                int choice,currUserID;
                currUserID = auth;

                sleep(1);
                system("clear");
                while(1){
                    
                    char customerMenu[]="1. View Account Balance\n2. Deposit Money\n3. Withdraw Money\n4. Send Money\n5. Apply for Loan\n6. View History\n7. Add Feedback\n8. Change Password\n9. Logout\nEnter Choice: ";
                    bzero(buff,BUFF_SIZE);
                    printf("\n-------------------Welcome-------------------\n");
                    printf("%s",customerMenu);
                    scanf("%d",&choice);

                    write(sockfd,&choice,sizeof(int));
                    
                    if(choice==1){
                        long int userBal;
                        read(sockfd,&userBal,sizeof(long int));
                        write(sockfd,"Sync",strlen("Sync"));
                        printf("Account Balance: %ld\n",userBal);
                    }else if(choice==2){
                        long int amount;

                        bzero(buff,BUFF_SIZE);
                        bytes = read(sockfd,buff,BUFF_SIZE-1);
                        buff[bytes] = '\0';
                        printf("%s",buff);
                        scanf("%ld",&amount);

                        write(sockfd,&amount,sizeof(long int));

                    }else if(choice==3){
                        long int amount;
                        printf("Enter amount: ");
                        scanf("%ld",&amount);
                        write(sockfd,&amount,sizeof(long int));
                    }else if(choice==4){

                    }
                    else if(choice==5){

                    }else if(choice==6){

                    }
                    else if(choice==7){

                    }else if(choice==8){
                        
                    }
                    else if(choice==9){
                        break;
                    }else{
                        
                    }
                }
            }
            /*
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
            */

        }
        else if(loginAct==2){
            break;
        }
    }
    close(sockfd);
    return 0;
}