#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>

#define BUFF_SIZE 1024
#define MAX_LEN 64

void semaphore_wait(int semid, int semnum) {
    struct sembuf sem_op;

    sem_op.sem_num = semnum;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;

    if (semop(semid, &sem_op, 1) == -1) {
        perror("Error performing P operation");
        exit(EXIT_FAILURE);
    }
}
void semaphore_signal(int semid, int semnum) {
    struct sembuf sem_op;

    sem_op.sem_num = semnum;
    sem_op.sem_op = 1;      
    sem_op.sem_flg = 0;     

    if (semop(semid, &sem_op, 1) == -1) {
        perror("Error performing V operation");
        exit(EXIT_FAILURE);
    }
}
void delete_semaphore(int semid) {
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Error deleting semaphore");
        exit(EXIT_FAILURE);
    }
}
int administratorZone(int sockfd,int currUserID,int *semid){
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
            semaphore_wait(*semid,3);
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
            semaphore_signal(*semid,3);
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

            write(sockfd,"Enter Employee ID: ",strlen("Enter Employee ID: "));
            bytes = read(sockfd,&UID,sizeof(int));

            int crossverify = userIdExist(UID);
            write(sockfd,&crossverify,sizeof(int));
            //sync wait
            read(sockfd,buff,BUFF_SIZE-1);
            if(crossverify==1){
                write(sockfd,"This ID is not available\n",strlen("This ID is not available\n"));
                continue;
            }

            write(sockfd,"Enter Username: ",strlen("Enter Username: "));
            bytes = read(sockfd,username,MAX_LEN-1);
            username[bytes]='\0';

            write(sockfd,"Enter Password: ",strlen("Enter Password: "));
            bytes = read(sockfd,pwd,MAX_LEN-1);
            pwd[bytes]='\0';

            //Check if the username/password already exist
            crossverify = login(username,pwd);
            write(sockfd,&crossverify,sizeof(int));
            read(sockfd,buff,BUFF_SIZE-1);
            if(crossverify!=-1){
                write(sockfd,"Username password already Exist.Please login\n",strlen("Username password already Exist.Please login\n"));
                continue;
            }

            write(sockfd,"Enter Name: ",strlen("Enter Name: "));
            bytes = read(sockfd,name,MAX_LEN-1);
            name[bytes]='\0';

            write(sockfd,"Enter Email: ",strlen("Enter Email: "));
            bytes = read(sockfd,email,MAX_LEN-1);
            email[bytes]='\0';

            write(sockfd,"Enter phone: ",strlen("Enter phone: "));
            bytes = read(sockfd,phone,MAX_LEN-1);
            phone[bytes]='\0';

            semaphore_wait(*semid,0);
            semaphore_wait(*semid,3);
            int registerExitStatus = register_user(UID,username,pwd,name,email,phone);
            semaphore_signal(*semid,0);
            semaphore_signal(*semid,3);
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

            semaphore_wait(*semid,0);
            int roleChangeStatus = managerUserRoles(oldID,newID);
            semaphore_signal(*semid,0);
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
            else if(userExistStatus!=currUserID){
                write(sockfd,"Wrong Credentials!\n",strlen("Wrong Credentials!\n"));
                continue;
            }

            //Get new password
            write(sockfd,"Enter New Password: ",strlen("Enter New Password: "));
            bytes = read(sockfd,newPwd,MAX_LEN);
            newPwd[bytes]='\0';

            //password change status
            semaphore_wait(*semid,0);
            int updateStatus = change_password(username,currPwd,newPwd);
            semaphore_signal(*semid,0);
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
int managerZone(int sockfd,int currUserID,int *semid){
    char buff[BUFF_SIZE];
    int choice;
    ssize_t bytes;

    while (1){
        read(sockfd,&choice,sizeof(int));
        
        if(choice==1){
            int custID;
            
            write(sockfd,"Enter Customer ID: ",strlen("Enter Customer ID: "));
            read(sockfd,&custID,sizeof(int));
            
            semaphore_wait(*semid,0);
            int status = active_deactiveUser(custID,1);
            semaphore_signal(*semid,0);
            if(status==1){
                write(sockfd,"Success!\n",strlen("Success!\n"));
            }else if(status==0){
                write(sockfd,"Already Activated\n",strlen("Already Activated\n"));
            }else if(status==-1){
                write(sockfd,"No User Found!\n",strlen("No User Found!\n"));
            }
            else if(status==-2){
                write(sockfd,"Failed to activate\n",strlen("Failed to activate\n"));
            }
            
        }else if(choice==2){
            int custID;
            write(sockfd,"Enter Customer ID: ",strlen("Enter Customer ID: "));
            read(sockfd,&custID,sizeof(int));

            semaphore_wait(*semid,0);
            int status = active_deactiveUser(custID,0);
            semaphore_signal(*semid,0);
            if(status==1){
                write(sockfd,"Success!\n",strlen("Success!\n"));
            }else if(status==0){
                write(sockfd,"Already deactivated\n",strlen("Already deactivated\n"));
            }else if(status==-1){
                write(sockfd,"No User Found!\n",strlen("No User Found!\n"));
            }
            else if(status==-2){
                write(sockfd,"Failed to deactivate\n",strlen("Failed to deactivate\n"));
            }
        }
        else if (choice==3){
            //Assigning loan to employee
            int employeeID;
            char loanID[16];

            write(sockfd,"Enter LoanID to assign: ",strlen("Enter LoanID to assign: "));
            read(sockfd,loanID,sizeof(loanID));
            printf("%s",loanID);

            write(sockfd,"Enter Employee ID to assign: ",strlen("Enter Employee ID to assign: "));
            read(sockfd,&employeeID,sizeof(int));

            if(userIdExist(employeeID)!=1){
                write(sockfd,"Employee Doesn't Exist\n",strlen("Employee Doesn't Exist\n"));
                continue;
            }

            semaphore_wait(*semid,1);
            int assginedStatus = assignLoanToEmployee(employeeID,loanID);
            semaphore_signal(*semid,1);
            if(assginedStatus==1){
                write(sockfd,"Successfully Assigned!\n",strlen("Successfully Assigned!\n"));
            }else if(assginedStatus==0){
                write(sockfd,"We don't have any loan Application from Customer\n",strlen("We don't have any loan Application from Customer\n"));
            }else if(assginedStatus==-1){
                write(sockfd,"No Such LoanID Exist\n",strlen("No Such LoanID Exist\n"));
            }
            else{
                write(sockfd,"Error Occured!\n",strlen("Error Occured!\n"));
            }
        }
        else if(choice==4){
            _Bool permission = 1;
            write(sockfd,&permission,sizeof(_Bool));
        }else if(choice==5){
            //Update Manager Password
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
            else if(userExistStatus!=currUserID){
                write(sockfd,"Wrong Credentials!\n",strlen("Wrong Credentials!\n"));
                continue;
            }
            
            //Get new password
            write(sockfd,"Enter New Password: ",strlen("Enter New Password: "));
            bytes = read(sockfd,newPwd,MAX_LEN);
            newPwd[bytes]='\0';

            //password change status
            semaphore_wait(*semid,0);
            int updateStatus = change_password(username,currPwd,newPwd);
            semaphore_signal(*semid,0);
            write(sockfd,&updateStatus,sizeof(int));
            //Sync code
            read(sockfd,buff,BUFF_SIZE-1);
            if(updateStatus!=currUserID){
                write(sockfd,"Failed to Update password\n",strlen("Failed to Update password\n"));
            }
            else
                write(sockfd,"Password Updated successfully\n",strlen("Password Updated successfully\n"));
        }else if (choice==6){
            _Bool permission = 1;
            write(sockfd,&permission,sizeof(_Bool));
        }
        else if(choice==7){break;}   
    }
    return 1;
}
int employeeZone(int sockfd,int currUserID,int *semid){
    char buff[BUFF_SIZE];
    int choice;
    ssize_t bytes;

    while(1){
        read(sockfd,&choice,sizeof(int));

        if(choice==1){
            int UID;
            char username[MAX_LEN];
            char pwd[MAX_LEN];
            char name[MAX_LEN];
            char email[MAX_LEN];
            char phone[MAX_LEN];

            write(sockfd,"Enter Customer ID: ",strlen("Enter Customer ID: "));
            bytes = read(sockfd,&UID,sizeof(int));

            int crossverify = userIdExist(UID);
            write(sockfd,&crossverify,sizeof(int));
            //sync wait
            read(sockfd,buff,BUFF_SIZE-1);
            if(crossverify==1){
                write(sockfd,"This ID is not available\n",strlen("This ID is not available\n"));
                continue;
            }

            write(sockfd,"Enter Username: ",strlen("Enter Username: "));
            bytes = read(sockfd,username,MAX_LEN-1);
            username[bytes]='\0';

            write(sockfd,"Enter Password: ",strlen("Enter Password: "));
            bytes = read(sockfd,pwd,MAX_LEN-1);
            pwd[bytes]='\0';
            //Check if username/password in use
            crossverify = login(username,pwd);
            write(sockfd,&crossverify,sizeof(int));
            read(sockfd,buff,BUFF_SIZE-1);
            if(crossverify!=-1){
                write(sockfd,"Username password already Exist.Please login\n",strlen("Username password already Exist.Please login\n"));
                continue;
            }

            write(sockfd,"Enter Name: ",strlen("Enter Name: "));
            bytes = read(sockfd,name,MAX_LEN-1);
            name[bytes]='\0';

            write(sockfd,"Enter Email: ",strlen("Enter Email: "));
            bytes = read(sockfd,email,MAX_LEN-1);
            email[bytes]='\0';

            write(sockfd,"Enter phone: ",strlen("Enter phone: "));
            bytes = read(sockfd,phone,MAX_LEN-1);
            phone[bytes]='\0';

            semaphore_wait(*semid,0);
            semaphore_wait(*semid,3);
            int registerExitStatus = register_user(UID,username,pwd,name,email,phone);
            semaphore_signal(*semid,0);
            semaphore_signal(*semid,3);
            if(registerExitStatus!=1)
                write(sockfd,"Failed to Register\n",strlen("Failed to Register\n"));
            else
                write(sockfd,"Registraion Success\n",strlen("Registraion Success\n"));
        }else if(choice==2){
            int uid,change,whichDetail,checkUpdateStatus,verifyUser;
            char name[MAX_LEN];
            char email[MAX_LEN];
            char phone[MAX_LEN];

            write(sockfd,"Enter Customer ID: ",strlen("Enter Customer ID: "));
            bytes = read(sockfd,&uid,sizeof(uid));

            verifyUser = userIdExist(uid);
            write(sockfd,&verifyUser,sizeof(int));
            read(sockfd,buff,BUFF_SIZE-1);
            if(verifyUser!=1){
                write(sockfd,"User doesn't Exit\n",strlen("User doesn't Exit\n"));
                continue;
            }

            write(sockfd,"Which detail to change?\n1. Name\n2. Email\n3. Phone\n",strlen("Which detail to change?\n1. Name\n2. Email\n3. Phone\n"));
            bytes = read(sockfd,&change,sizeof(int));

            write(sockfd,"sync",strlen("sync"));
            semaphore_wait(*semid,3);
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
            semaphore_signal(*semid,3);
        }
        else if(choice==3){
            //Process Loan
            char loanID[20];

            write(sockfd,"Enter LoanID: ",strlen("Enter LoanID: "));
            read(sockfd,loanID,sizeof(loanID));

            semaphore_wait(*semid,1);
            int processStatus = processLoan(currUserID,loanID);
            semaphore_signal(*semid,1);
            if(processStatus==0)
                write(sockfd,"No Such LoanID Exist\n",strlen("No Such LoanID Exist\n"));
            else if(processStatus==1)
                write(sockfd,"Success!\n",strlen("Success!\n"));
            else
                write(sockfd,"Failed to process Loan\n",strlen("Failed to process Loan\n"));
        }
        else if(choice==4){
            //Acccpt/Reject Loan
            char loanID[20];
            int act;

            write(sockfd,"Enter LoanID: ",strlen("Enter LoanID: "));
            read(sockfd,loanID,sizeof(loanID));

            write(sockfd,"1. Accept\n2. Reject\n",strlen("1. Accept\n2. Reject\n"));
            read(sockfd,&act,sizeof(int));

            semaphore_wait(*semid,1);
            int acceptanceStatus = accept_rejectLoanApp(currUserID,loanID,act);
            semaphore_signal(*semid,1);
            if(acceptanceStatus==0)
                write(sockfd,"No Such LoanID Exist\n",strlen("No Such LoanID Exist\n"));
            else if(acceptanceStatus==1)
                write(sockfd,"Success!\n",strlen("Success!\n"));
            else
                write(sockfd,"Failed to process Loan\n",strlen("Failed to process Loan\n"));
        }
        else if(choice==5){
            _Bool permission = 1;
            write(sockfd,&permission,sizeof(_Bool));
        }
        else if(choice==6){
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
            else if(userExistStatus!=currUserID){
                write(sockfd,"Wrong Credentials!\n",strlen("Wrong Credentials!\n"));
                continue;
            }

            //Get new password
            write(sockfd,"Enter New Password: ",strlen("Enter New Password: "));
            bytes = read(sockfd,newPwd,MAX_LEN);
            newPwd[bytes]='\0';

            //password change status
            semaphore_wait(*semid,0);
            int updateStatus = change_password(username,currPwd,newPwd);
            semaphore_signal(*semid,0);
            write(sockfd,&updateStatus,sizeof(int));
            //Sync code
            read(sockfd,buff,BUFF_SIZE-1);
            if(updateStatus!=currUserID){
                write(sockfd,"Failed to Update password\n",strlen("Failed to Update password\n"));
            }
            else
                write(sockfd,"Password Updated successfully\n",strlen("Password Updated successfully\n"));
        }
        else if(choice==7){break;}
    }
    return 1;
}
int customerZone(int sockfd,int currUserID,int *semid){
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
            
            semaphore_wait(*semid,4);
            if(depositFund(currUserID,currUserID,amount)!=1){
                fprintf(stderr,"Couldn't credit money\n");
            }
            semaphore_signal(*semid,4);
        }
        else if(mychoice==3){
            long int amount;
            read(sockfd,&amount,sizeof(long int));

            semaphore_wait(*semid,5);
            int debitStatus = withdrawFund(currUserID,currUserID,amount);
            semaphore_signal(*semid,5);

            if(debitStatus==0)
                write(sockfd,"Not enough Balance\n",strlen("Not enough Balance\n"));
            else if(debitStatus==1)
                write(sockfd,"Success\n",strlen("Success\n"));
            else
                write(sockfd,"Failed to withdraw\n",strlen("Failed to withdraw\n"));
        }
        else if(mychoice==4){
            int towhom,validUser;
            long int amount;

            write(sockfd,"Send to UserID: ",strlen("Send to UserID: "));
            read(sockfd,&towhom,sizeof(int));

            validUser = userIdExist(towhom);
            write(sockfd,&validUser,sizeof(int));
            read(sockfd,buff,BUFF_SIZE-1);
            if(validUser!=1){
                write(sockfd,"No such User Exist!\n",strlen("No such User Exist!\n"));
                continue;
            }

            write(sockfd,"Enter Amount: ",strlen("Enter Amount: "));
            //sync wait
            read(sockfd,&amount,sizeof(long int));
            
            semaphore_wait(*semid,5);
            if(withdrawFund(currUserID,towhom,amount)!=1){
                write(sockfd,"Not enough Balance\n",strlen("Not enough Balance\n"));
            }
            semaphore_signal(*semid,5);
            
            semaphore_wait(*semid,4);
            if(depositFund(towhom,currUserID,amount)!=1){
                write(sockfd,"Failed to send money\n",strlen("Failed to send money\n"));
            }
            semaphore_signal(*semid,4);

            write(sockfd,"Transfered Successfully \n",strlen("Transfered Successfully \n"));
        }
        else if(mychoice==5){
            //Apply for Loan
            long int amount;
            read(sockfd,&amount,sizeof(long int));
            
            semaphore_wait(*semid,1);
            int status = applytoLoan(currUserID,amount);
            semaphore_signal(*semid,1);

            if(status!=1) write(sockfd,"Error occure. Please try again!",strlen("Error occure. Please try again!"));
            else write(sockfd,"Loan Application Submitted Successfully\n",strlen("Loan Application Submitted Successfully\n"));
        }else if(mychoice==6){
            _Bool permission = 1;
            write(sockfd,&permission,sizeof(_Bool));
        }else if(mychoice==7){
            //Take feedback
            int stars;
            char feedback[256];

            write(sockfd,"Love our service? please rate us(1-10)\n",strlen("Love our service? please rate us(1-10)\n"));
            read(sockfd,&stars,sizeof(int));

            write(sockfd,"Please write Feedback: ",strlen("Please write Feedback: "));
            bytes = read(sockfd,feedback,sizeof(feedback));

            semaphore_wait(*semid,2);
            int status = addFeedback(stars,feedback);
            semaphore_signal(*semid,2);

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

            semaphore_wait(*semid,0);
            int uid = change_password(username,currPass,newPass);
            semaphore_signal(*semid,0);
            if(uid<=0) write(sockfd,"Error changin password\n",strlen("Error changin password\n"));
            else write(sockfd,"Password changed Successfully\n",strlen("Password changed Successfully\n"));
        }
        else if (mychoice==9){
            _Bool permission = 1;
            write(sockfd,&permission,sizeof(_Bool));
        }
        else if(mychoice==10){break;}
    }
    return 1;
}