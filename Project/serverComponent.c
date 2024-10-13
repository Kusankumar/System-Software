#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <sys/stat.h>

#define MAX_LEN 64
#define PATH_LEN 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <sys/stat.h>

#define MAX_LEN 64
#define PATH_LEN 64

struct credential {
    int UID;
    _Bool active;
    char username[MAX_LEN];
    char password[MAX_LEN];
};

struct userDetails{
    int UID;
    char name[MAX_LEN];
    char email[MAX_LEN];
    char phone[MAX_LEN];
    char designation[MAX_LEN];
};

struct acbalance{
    long int balance;
};

struct transHistory{
    int fromID;
    int toID;
    char type[MAX_LEN];
    long int balance;
};

struct feedback{
    int star;
    char fb[256];
};

struct assignedLoan {
    char loanID[MAX_LEN];
    int uid;
    char username[MAX_LEN];
    long int amount;
    char status[MAX_LEN];
};

struct loanApplication{
    char loanID[MAX_LEN];
    int applicationNo;
    long int amount;
    char status[MAX_LEN];
};
int modifyUserDetail(int userID,int whichEntry,char *newEntry){
    struct userDetails udetail,fileUser;
    off_t offset = 0;
    _Bool found = 0;
    char path[PATH_LEN];

    snprintf(path,PATH_LEN,"%d/userdetail.dat",userID);
    int fd = open(path,O_RDWR);
    if(fd<0){
        perror("Error opening User Detail file");
        return -1;
    }

    while(read(fd,&fileUser,sizeof(struct userDetails))>0){
        if(fileUser.UID==userID){
            found = 1;
            break;
        }
        offset += sizeof(struct userDetails);
    }

    if(!found){
        printf("No User Found\n");
        close(fd);
        return -1;
    }

    udetail.UID = userID;
    snprintf(udetail.name,MAX_LEN,"%s",fileUser.name);
    snprintf(udetail.email,MAX_LEN,"%s",fileUser.email);
    snprintf(udetail.phone,MAX_LEN,"%s",fileUser.phone);
    snprintf(udetail.designation,MAX_LEN,"%s",fileUser.designation);

    if(whichEntry==1){
        snprintf(udetail.name,MAX_LEN,"%s",newEntry);
    }else if(whichEntry==2){
        snprintf(udetail.email,MAX_LEN,"%s",newEntry);
    }else if(whichEntry==3){
        snprintf(udetail.phone,MAX_LEN,"%s",newEntry);
    }

    lseek(fd,offset,SEEK_SET);
    if(write(fd,&udetail,sizeof(struct userDetails))<0){
        perror("Error writing on user file");
        close(fd);
        return -1;
    }
    close(fd);
    return 1;
}

int login(char uname[MAX_LEN],char upwd[MAX_LEN]) {
    struct credential file_user;

    int fd = open("credentials.dat", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return -1;
    }

    while (read(fd, &file_user, sizeof(struct credential)) > 0) {
        if (strcmp(uname, file_user.username) == 0 &&
            strcmp(upwd, file_user.password) == 0) {
            close(fd);
            if(file_user.active==0) return 0;
            return file_user.UID;
        }
    }

    close(fd);
    return -1;
}

int register_user(int uid,char *username,char *pwd,char* name,char* uemail,char* phone) {
    struct credential user;
    struct userDetails udetail;
    struct acbalance ubal;
    struct transHistory utrans;
    struct feedback ufeed;
    char path[PATH_LEN];

    //Input credentials
    user.UID = uid;
    user.active =1;
    snprintf(user.username,MAX_LEN,"%s",username);
    snprintf(user.password,MAX_LEN,"%s",pwd);
    
    
    udetail.UID = user.UID;
    snprintf(udetail.name,MAX_LEN,"%s",name);
    snprintf(udetail.email,MAX_LEN,"%s",uemail);
    snprintf(udetail.phone,MAX_LEN,"%s",phone);
    
    if(user.UID>1000){
        snprintf(udetail.designation,MAX_LEN,"%s","Customer");
    }
    else if(user.UID>200 && user.UID<=1000){
        snprintf(udetail.designation,MAX_LEN,"%s","Employee");
    }
    else if(user.UID>50 && user.UID<=200){
        snprintf(udetail.designation,MAX_LEN,"%s","Manager");
    }
    else if(user.UID>=1 && user.UID<=50){
        snprintf(udetail.designation,MAX_LEN,"%s","Administrator");
    }
    //User bank balance Intialize
    ubal.balance = 0;

    int fd = open("credentials.dat", O_WRONLY | O_APPEND | O_CREAT, 0600);
    if (fd < 0) {
        perror("Error opening file");
        return 0;
    }

    if (write(fd, &user, sizeof(struct credential)) < 0) {
        perror("Error writing to file");
        close(fd);
        return 0;
    }
    close(fd);

    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d",user.UID);
    mkdir(path,0766);


    //Creating User detail File
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d/userdetail.dat",user.UID);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> files",path);
    write(fd,&udetail,sizeof(struct userDetails));
    close(fd);

    //Creating User File for account balance
    if(user.UID>1000){
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d/balance.dat",user.UID);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> files",path);
    write(fd,&ubal,sizeof(struct acbalance));
    close(fd);

    //Creating User Transaction History file
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d/transactionHist.dat",user.UID);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
    close(fd);

    //Creating User Feedback File
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d/feedback.dat",user.UID);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
    close(fd);

    //Creating User Loan detail file
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d/userloandetail.dat",user.UID);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
    close(fd);
    }

    //Create Employee assigned loan file
    if(user.UID>200 && user.UID<=1000){
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/assignedloan.dat",user.UID);

        fd = open(path,O_WRONLY|O_CREAT,0766);
        if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
        close(fd);
    }
    return 1;
}
//change password
int change_password(char *username,char *currpass,char *newpass) {
    struct credential user, file_user;
    int found = 0;

    snprintf(user.username,MAX_LEN,"%s",username);
    snprintf(user.password,MAX_LEN,"%s",currpass);

    int fd = open("credentials.dat", O_RDWR);
    if (fd < 0) {
        perror("Error opening file");
        return -1;
    }

    // Search for the user and get the file offset
    off_t offset = 0;
    while (read(fd, &file_user, sizeof(struct credential)) > 0) {
        if (strcmp(user.username, file_user.username) == 0 &&
            strcmp(user.password, file_user.password) == 0) {
            found = 1;
            break;
        }
        offset += sizeof(struct credential);
    }

    if (!found) {
        printf("No User Found\n");
        close(fd);
        return 0;
    }

    //Setting new Password
    snprintf(user.password,MAX_LEN,"%s",newpass);
    user.UID=file_user.UID;
    user.active=file_user.active;

    lseek(fd, offset, SEEK_SET);

    if (write(fd, &user, sizeof(struct credential)) < 0) {
        perror("Error writing to file");
        close(fd);
        return -1;
    }
    close(fd);
    return user.UID;
}
void transactionEntry(int userID,int toUserID,char *type,long int bal){
    struct transHistory tranHist;
    char path[PATH_LEN];

    tranHist.fromID = userID;
    tranHist.toID = toUserID;
    snprintf(tranHist.type,MAX_LEN,"%s",type);
    tranHist.balance = bal;

    snprintf(path,PATH_LEN,"%d/transactionHist.dat",userID);
    int fd = open(path,O_WRONLY|O_CREAT|O_APPEND,0766);
    if(fd<0) perror("Error opening transaction History file");
    
    if(write(fd,&tranHist,sizeof(struct transHistory))<0){
        perror("Error writing transaction history\n");
        return;
    }
    close(fd);
}

long int checkUserBalance(int userID){
    struct acbalance bal;
    char path[PATH_LEN];

    snprintf(path,PATH_LEN,"%d/balance.dat",userID);
    int fd = open(path,O_RDONLY);
    if(fd<0) perror("Error opening balance file");
    
    read(fd,&bal,sizeof(struct acbalance));
    
    close(fd);
    return bal.balance;
}

int depositFund(int userID,int touserID,long int addAmount){
    struct acbalance bal;
    char path[PATH_LEN];

    snprintf(path,PATH_LEN,"%d/balance.dat",userID);
    int fd = open(path,O_RDWR);
    if(fd<0) perror("Error opening balance file");
    
    read(fd,&bal,sizeof(struct acbalance));
    bal.balance = bal.balance + addAmount;
    lseek(fd,0,SEEK_SET);

    write(fd,&bal,sizeof(struct acbalance));
    close(fd);

    transactionEntry(userID,touserID,"credit",addAmount);
    return 1;
}

int withdrawFund(int userID,int touserID,long int debitAmount){
    struct acbalance bal;
    char path[PATH_LEN];

    snprintf(path,PATH_LEN,"%d/balance.dat",userID);
    int fd = open(path,O_RDWR);
    if(fd<0) perror("Error opening balance file");
    
    read(fd,&bal,sizeof(struct acbalance));
    bal.balance = bal.balance - debitAmount;
    lseek(fd,0,SEEK_SET);

    write(fd,&bal,sizeof(struct acbalance));
    close(fd);

    transactionEntry(userID,touserID,"debit",debitAmount);
    return 1;
}

int userIdExist(int userID){
    struct credential ucred;
    
    int fd = open("credentials.dat",O_RDONLY);
    while (read(fd,&ucred,sizeof(struct credential))>0){
        if(ucred.UID==userID){
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;
}

int managerUserRoles(int oldID,int newID){
    struct userDetails currDetail;
    struct credential currCred;
    char path[PATH_LEN];
    _Bool found = 0;
    off_t offset = 0;

    int fd = open("credentials.dat",O_RDWR);
    if(fd<0){
        perror("Error Opening credentials.dat");
        return -1;
    }

    while (read(fd,&currCred,sizeof(struct credential))>0){
        if(currCred.UID==oldID){
            found = 1;
            break;
        }
        offset+=sizeof(struct credential);
    }

    if(!found){
        printf("No User Found\n");
        close(fd);
        return -1;
    }

    currCred.UID = newID;
    lseek(fd,offset,SEEK_SET);
    if(write(fd,&currCred,sizeof(struct credential))<0){
        perror("Error updating credential");
        close(fd);
        return -1;
    }
    close(fd);

    //reading old detail
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d/userdetail.dat",oldID);
    fd = open(path,O_RDWR);
    if(fd<0){
        perror("Error Opening userdetail.dat");
        return -1;
    }
    if(read(fd,&currDetail,sizeof(struct userDetails))<0){
        perror("Error Reading User Info");
        close(fd);
        return -1;
    }
    currDetail.UID=newID;
    if(newID>1000){
        snprintf(currDetail.designation,MAX_LEN,"%s","Customer");
    }
    else if(newID>200 && newID<=1000){
        snprintf(currDetail.designation,MAX_LEN,"%s","Employee");
    }
    else if(newID>50 && newID<=200){
        snprintf(currDetail.designation,MAX_LEN,"%s","Manager");
    }
    else if(newID>=1 && newID<=50){
        snprintf(currDetail.designation,MAX_LEN,"%s","Administrator");
    }

    lseek(fd,0,SEEK_SET);
    if(write(fd,&currDetail,sizeof(struct userDetails))<0){
        perror("Error writing new detail");
        close(fd);
        return -1;
    }
    close(fd);
    
    if(newID>1000){
        //Creating User balance sheet
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/balance.dat",oldID);

        fd = open(path,O_WRONLY|O_CREAT,0766);
        if(fd<0) fprintf(stderr,"Error creating <%s> files",path);
        close(fd);

        //Creating User Transaction History file
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/transactionHist.dat",oldID);

        fd = open(path,O_WRONLY|O_CREAT,0766);
        if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
        close(fd);

        //Creating User Feedback File
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/feedback.dat",oldID);

        fd = open(path,O_WRONLY|O_CREAT,0766);
        if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
        close(fd);

        //Creating User Loan detail file
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/userloandetail.dat",oldID);

        fd = open(path,O_WRONLY|O_CREAT,0766);
        if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
        close(fd);

        //Deleting files not related to user
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/assignedloan.dat",oldID);
        unlink(path);
    }
    else if(newID>200 && newID<=1000){
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/balance.dat",oldID);
        unlink(path);

        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/transactionHist.dat",oldID);
        unlink(path);

        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/feedback.dat",oldID);
        unlink(path);

        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/userloandetail.dat",oldID);
        unlink(path);
        
        //Creating new file specific for employee
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/assignedloan.dat",oldID);
        open(path,O_RDONLY|O_CREAT,0766);
    }
    else if(newID>50 && newID<=200){
        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/balance.dat",oldID);
        unlink(path);

        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/transactionHist.dat",oldID);
        unlink(path);

        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/feedback.dat",oldID);
        unlink(path);

        bzero(path,PATH_LEN);
        snprintf(path,PATH_LEN,"%d/userloandetail.dat",oldID);
        unlink(path);
    }

    char oldDir[MAX_LEN],newDir[MAX_LEN];
    snprintf(oldDir,MAX_LEN,"%d",oldID);
    snprintf(newDir,MAX_LEN,"%d",newID);
    rename(oldDir,newDir);
    return 1; 
}

//Loan Component
int sendLoanAppToManager(struct userDetails user,struct loanApplication loanForm){
    struct assignedLoan recievedForm;

    recievedForm.amount=loanForm.amount;
    snprintf(recievedForm.loanID,MAX_LEN,"%s",loanForm.loanID);
    snprintf(recievedForm.status,MAX_LEN,"%s",loanForm.status);

    recievedForm.uid=user.UID;
    snprintf(recievedForm.username,MAX_LEN,"%s",user.name);

    int fd = open("managerDB/loanApplication.dat",O_WRONLY|O_APPEND);
    if(fd<0) {
        perror("Error opening managerDB/loanApplication.dat");
        return -1;
    }
    if(write(fd,&recievedForm,sizeof(struct assignedLoan))<0){
        perror("Error assiging loan application");
        close(fd);
        return -1;
    }
    return 1;
}
int applytoLoan(int userID,long int amount){
    struct loanApplication loanForm;
    struct userDetails user;
    char path[PATH_LEN];
    off_t offset;

    snprintf(path,PATH_LEN,"%d/userloandetail.dat",userID);
    int fd = open(path,O_RDONLY);
    if(fd<0) {
        perror("Error opening userloandetail.dat");
        return -1;
    }

    ssize_t bytes = read(fd,&loanForm,sizeof(struct loanApplication));
    if(bytes==0){
        loanForm.applicationNo = 1;
    }else if(bytes>0){
        lseek(fd, 0, SEEK_END);
        lseek(fd, -sizeof(struct loanApplication), SEEK_END);
        if(read(fd,&loanForm,sizeof(struct loanApplication))<0){
            perror("Error reading user loan detail");
            close(fd);
            return -1;
        }
        loanForm.applicationNo+=1;
    }else{
        perror("Error reading userloandetail.dat");
        close(fd);
        return -1;
    }
    close(fd);
    snprintf(loanForm.loanID,MAX_LEN,"%d%d",userID,loanForm.applicationNo);
    loanForm.amount=amount;
    snprintf(loanForm.status,MAX_LEN,"%s","pending");

    fd = open(path,O_WRONLY|O_APPEND);
    if(fd<0) {
        perror("Error opening userloandetail.dat");
        return -1;
    }
    if(write(fd,&loanForm,sizeof(struct loanApplication))<0){
        perror("Error applying to Loan");
        close(fd);
        return -1;
    }
    close(fd);

    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%d/userdetail.dat",userID);
    fd = open(path,O_RDONLY);
    if(fd<0) {
        perror("Error opening userdetail.dat");
        return -1;
    }
    if(read(fd,&user,sizeof(struct userDetails))<0){
        perror("Error reading user detail");
        close(fd);
        return -1;
    }
    sendLoanAppToManager(user,loanForm);
    return 1;
}
int addFeedback(int starRating, const char *feedbackMessage) {
    struct feedback fbEntry;
    int fd;

    fbEntry.star = starRating;
    snprintf(fbEntry.fb, sizeof(fbEntry.fb), "%s", feedbackMessage);

    fd = open("managerDB/feedback.dat", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening feedback.dat");
        return -1;
    }

    if (write(fd, &fbEntry, sizeof(struct feedback)) < 0) {
        perror("Error writing feedback");
        return -1;
    }
    close(fd);
    return 1;
}
