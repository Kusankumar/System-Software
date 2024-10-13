#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFF_SIZE 1024
#define MAX_LEN 64

int administratorZone(int sockfd,int currUserID){
    ssize_t bytes;
    char buff[BUFF_SIZE];
    int choice;

    while (1)
    {
        //Getting Menu  choice
        read(sockfd,&choice,sizeof(int));

        if(choice==1 || choice==2){
            int uid,change,whichDetail,checkUpdateStatus;
            char name[MAX_LEN];
            char email[MAX_LEN];
            char phone[MAX_LEN];

            if(choice==1)
                write(sockfd,"Enter Emplyoee ID: ",strlen("Enter Emplyoee ID: "));
            else
                write(sockfd,"Enter Customer ID: ",strlen("Enter Customer ID: "));
            bytes = read(sockfd,&uid,sizeof(uid));

            write(sockfd,"Which detail to change?\n1. Name\n2. Email\n3. Phone\n",strlen("Which detail to change?\n1. Name\n2. Email\n3. Phone\n"));
            bytes = read(sockfd,&change,sizeof(int));

            write(sockfd,"sync",strlen("sync"));
            if(change==1){
                //Get new Name
                bytes = read(sockfd,name,MAX_LEN-1);
                name[bytes]='\0';

                checkUpdateStatus = modifyUserDetail(uid,change,name);
            }else if(change==2){
                //Get new Email
                bytes = read(sockfd,email,MAX_LEN-1);
                name[bytes]='\0';

                checkUpdateStatus = modifyUserDetail(uid,change,email);
            }else if(change==3){
                //Get new phone
                bytes = read(sockfd,phone,MAX_LEN-1);
                name[bytes]='\0';

                checkUpdateStatus = modifyUserDetail(uid,change,phone);                
            }
            if(checkUpdateStatus!=1) write(sockfd,"Failed to update\n",strlen("Failed to update\n"));
            else write(sockfd,"Successfully Updated\n",strlen("Successfully Updated\n"));
        }
        else if(choice==3){
            //Register new Employee
            int UID;
            char username[MAX_LEN];
            char pwd[MAX_LEN];
            char name[MAX_LEN];
            char email[MAX_LEN];
            char phone[MAX_LEN];

            write(sockfd,"Enter User ID: ",strlen("Enter User ID: "));
            bytes = read(sockfd,&UID,sizeof(int));

            write(sockfd,"Enter Username: ",strlen("Enter Username: "));
            bytes = read(sockfd,username,MAX_LEN-1);
            username[bytes]='\0';

            write(sockfd,"Enter Password: ",strlen("Enter Password: "));
            bytes = read(sockfd,pwd,MAX_LEN-1);
            pwd[bytes]='\0';

            write(sockfd,"Enter Name: ",strlen("Enter Name: "));
            bytes = read(sockfd,name,MAX_LEN-1);
            name[bytes]='\0';

            write(sockfd,"Enter Email: ",strlen("Enter Email: "));
            bytes = read(sockfd,email,MAX_LEN-1);
            email[bytes]='\0';

            write(sockfd,"Enter phone: ",strlen("Enter phone: "));
            bytes = read(sockfd,phone,MAX_LEN-1);
            phone[bytes]='\0';

            int registerExitStatus = register_user(UID,username,pwd,name,email,phone);
            if(registerExitStatus!=1)
                write(sockfd,"Failed to Register\n",strlen("Failed to Register\n"));
            else
                write(sockfd,"Registraion Success\n",strlen("Registraion Success\n"));

        }
        else if(choice==4){
            //Manage User roles
            int oldID,newID,valid;

            write(sockfd,"Whose role you wants to change?\n",strlen("Whose role you wants to change?\n"));
            read(sockfd,&oldID,sizeof(int));

            valid = userIdExist(oldID);
            write(sockfd,&valid,sizeof(int));
            //sync wait
            read(sockfd,buff,MAX_LEN-1);
            if(valid==0){
                write(sockfd,"User doesn't Exist\n",strlen("User doesn't Exist\n"));
                continue;
            }

            //When User exist
            if(oldID>1000){
                write(sockfd,"Assign Role:\n1. Manager\n2. Employee\n",strlen("Assign Role:\n1. Manager\n2. Employee\n"));
                read(sockfd,&newID,sizeof(int));
            }
            else if(oldID>200 && oldID<=1000){
                write(sockfd,"Assign Role:\n1. Manager\n2. Customer\n",strlen("Assign Role:\n1. Manager\n2. Customer\n"));
                read(sockfd,&newID,sizeof(int));
            }
            else if(oldID>50 && oldID<=200){
                write(sockfd,"Assign Role:\n1. Customer\n2. Employee\n",strlen("Assign Role:\n1. Customer\n2. Employee\n"));
                read(sockfd,&newID,sizeof(int));
            }

            valid = userIdExist(newID);
            write(sockfd,&valid,sizeof(int));
            //sync wait
            read(sockfd,buff,MAX_LEN-1);
            if(valid==1){
                write(sockfd,"User already Exist\n",strlen("User already Exist\n"));
                continue;
            }

            int roleChangeStatus = managerUserRoles(oldID,newID);
            write(sockfd,&roleChangeStatus,sizeof(int));
            //sync wait
            read(sockfd,buff,MAX_LEN-1);
            if(roleChangeStatus!=1){
                write(sockfd,"Failed to Update role\n",strlen("Failed to Update role\n"));
            }
            else{
                write(sockfd,"Role updated successfully\n",strlen("Role updated successfully\n"));
            }
        }
        else if(choice==5){
            char username[MAX_LEN],currPwd[MAX_LEN],newPwd[MAX_LEN];

            write(sockfd,"Enter Username: ",strlen("Enter Username: "));
            bytes = read(sockfd,username,MAX_LEN);
            username[bytes]='\0';

            write(sockfd,"Enter Current Password: ",strlen("Enter Current Password: "));
            bytes = read(sockfd,currPwd,MAX_LEN);
            currPwd[bytes]='\0';

            //verify account
            int userExistStatus = login(username,currPwd);
            write(sockfd,&userExistStatus,sizeof(int));
            //Sync code
            read(sockfd,buff,BUFF_SIZE-1);
            if(userExistStatus==0){
                write(sockfd,"Account is Deactive\n",strlen("Account is Deactive\n"));
                continue;
            }
            else if(userExistStatus<0){
                write(sockfd,"No User Found\n",strlen("No User Found\n"));
                continue;
            }

            //Get new password
            write(sockfd,"Enter New Password: ",strlen("Enter New Password: "));
            bytes = read(sockfd,newPwd,MAX_LEN);
            newPwd[bytes]='\0';

            //password change status
            int updateStatus = change_password(username,currPwd,newPwd);
            write(sockfd,&updateStatus,sizeof(int));
            //Sync code
            read(sockfd,buff,BUFF_SIZE-1);
            if(updateStatus!=currUserID){
                write(sockfd,"Failed to Update password\n",strlen("Failed to Update password\n"));
            }
            else
                write(sockfd,"Password Updated successfully\n",strlen("Password Updated successfully\n"));

        }
        else if(choice==6)break;
    }
    
    return 1;
}

int customerZone(int sockfd,int currUserID){
    char username[32],userpwd[32],usermail[32];
    ssize_t bytes;
    char buff[BUFF_SIZE];
    int mychoice;

    while(1){
        read(sockfd,&mychoice,sizeof(int));

        if(mychoice==1){
            long int userBal = checkUserBalance(currUserID);
            write(sockfd,&userBal,sizeof(long int));
            //Sync wait
            read(sockfd,buff,BUFF_SIZE-1);
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
            //Apply for Loan
            long int amount;
            read(sockfd,&amount,sizeof(long int));
            int status = applytoLoan(currUserID,amount);
            if(status!=1) write(sockfd,"Error occure. Please try again!",strlen("Error occure. Please try again!"));
            else write(sockfd,"Loan Application Submitted Successfully\n",strlen("Loan Application Submitted Successfully\n"));
        }else if(mychoice==6){

        }else if(mychoice==7){
            //Take feedback
            int stars;
            char feedback[256];

            write(sockfd,"Love our service? please rate us(1-10)\n",strlen("Love our service? please rate us(1-10)\n"));
            read(sockfd,&stars,sizeof(int));

            write(sockfd,"Please write Feedback: ",strlen("Please write Feedback: "));
            bytes = read(sockfd,feedback,sizeof(feedback));

            int status = addFeedback(stars,feedback);
            if(status!=1) write(sockfd,"Failed to add Feedback\n",strlen("Failed to add Feedback\n"));
            else write(sockfd,"Feedback added successfully\n",strlen("Feedback added successfully\n"));

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
        else if(mychoice==10){break;}
    }
    return 1;
}