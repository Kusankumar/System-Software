#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define BUFF_Size 1024
#define MAX_LEN 64
int customerZone(int sockfd,int currUserID){
    char username[32],userpwd[32],usermail[32];
    ssize_t bytes;
    char buff[BUFF_Size];
    int mychoice;

    while(1){
        read(sockfd,&mychoice,sizeof(int));

        if(mychoice==1){
            long int userBal = checkUserBalance(currUserID);
            write(sockfd,&userBal,sizeof(long int));
            //Sync wait
            read(sockfd,buff,BUFF_Size-1);
        }
        else if(mychoice==2){
            long int amount;
            write(sockfd,"Enter deposit amount: ",strlen("Enter deposit amount: "));
            read(sockfd,&amount,sizeof(long int));
            if(depositFund(currUserID,currUserID,amount)!=1){
                fprintf(stderr,"Couldn't credit money\n");
            }
        }
        else if(mychoice==3){
            long int amount;
            read(sockfd,&amount,sizeof(long int));
            if(withdrawFund(currUserID,currUserID,amount)!=1){
                fprintf(stderr,"Couldn't deposit money\n");
            }
        }
        else if(mychoice==4){
            int towhom;
            long int amount;

            write(sockfd,"Send to UserID: ",strlen("Send to UserID: "));
            read(sockfd,&towhom,sizeof(int));;

            write(sockfd,"Enter Amount: ",strlen("Enter Amount: "));
            read(sockfd,&amount,sizeof(long int));

            if(withdrawFund(currUserID,towhom,amount)!=1){
                fprintf(stderr,"Couldn't deposit money\n");
            }

            if(depositFund(towhom,currUserID,amount)!=1){
                fprintf(stderr,"Couldn't credit money\n");
            } 
            write(sockfd,"sync",strlen("sync"));
        }
        else if(mychoice==5){

        }else if(mychoice==6){

        }else if(mychoice==7){

        }else if(mychoice==8){
            //Change password
            char username[MAX_LEN],currPass[MAX_LEN],newPass[MAX_LEN];
            
            write(sockfd,"Enter Username: ",strlen("Enter Username: "));
            read(sockfd,username,MAX_LEN-1);

            write(sockfd,"Enter Current Password: ",strlen("Enter Current Password: "));
            read(sockfd,currPass,MAX_LEN-1);

            write(sockfd,"Enter New Password: ",strlen("Enter New Password: "));
            read(sockfd,newPass,MAX_LEN-1);

            int uid = change_password(username,currPass,newPass);
            if(uid<=0) write(sockfd,"Error changin password\n",strlen("Error changin password\n"));
            else write(sockfd,"Password changed Successfully\n",strlen("Password changed Successfully\n"));
            
        }
        else if(mychoice==9){
            break;
        }
    }
    return 1;
}