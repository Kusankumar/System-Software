#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int customerZone(int sockfd,int currUserID){
    char username[32],userpwd[32],usermail[32];
    ssize_t bytes;
    int mychoice;

    while(1){
        read(sockfd,&mychoice,sizeof(int));

        if(mychoice==1){
            long int userBal = checkUserBalance(currUserID);
            write(sockfd,&userBal,sizeof(long int));
            read(sockfd,"Sync",strlen("Sync"));
        }
        else if(mychoice==2){
            long int amount;
            write(sockfd,"Enter deposit amount: ",strlen("Enter deposit amount: "));
            read(sockfd,&amount,sizeof(long int));
            if(depositFund(currUserID,amount)!=1){
                fprintf(stderr,"Couldn't credit money\n");
            }
        }
        else if(mychoice==3){
            long int amount;
            read(sockfd,&amount,sizeof(long int));
            if(withdrawFund(currUserID,amount)!=1){
                fprintf(stderr,"Couldn't deposit money\n");
            }
        }/*
        else if(mychoice==4){
            
        }
        else if(mychoice==5){

        }else if(mychoice==6){

        }else if(mychoice==7){

        }else if(mychoice==8){

        }
        */
        else if(mychoice==9){
            break;
        }
        else{

        }
    }
    return 1;
}