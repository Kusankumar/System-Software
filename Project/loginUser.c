#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <sys/stat.h>

#define MAX_LEN 64
#define PATH_LEN 64
#define DIR_LEN 16

struct credential {
    int UID;
    char username[MAX_LEN];
    char password[MAX_LEN];
};

struct userDetails{
    int UID;
    char name[MAX_LEN];
    char email[MAX_LEN];
    char phone[MAX_LEN];
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

struct feedback
{
    int star;
    char fb[256];
};

struct loan
{
    int loanID;
    int loanCount;
    int approved;
    int rejected;
    int pending;
};


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

    lseek(fd, offset, SEEK_SET);

    if (write(fd, &user, sizeof(struct credential)) < 0) {
        perror("Error writing to file");
        close(fd);
        return -1;
    }
    close(fd);
    return user.UID;
}

void deleterecord(const char* uname, const char* pwd) {
    struct credential nextRecord;
    int fd1 = open("credentials.dat", O_RDONLY);
    if (fd1 < 0) {
        perror("Error opening credentials.dat");
        return;
    }

    int fd2 = open("temp.dat", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 < 0) {
        perror("Error opening temp.dat");
        close(fd1);
        return;
    }

    while (read(fd1, &nextRecord, sizeof(struct credential)) > 0) {
        if (strcmp(nextRecord.username, uname) == 0 &&
            strcmp(nextRecord.password, pwd) == 0) {
            continue;
        }
        write(fd2, &nextRecord, sizeof(struct credential));
    }

    close(fd1);
    close(fd2);

    remove("credentials.dat");
    rename("temp.dat", "credentials.dat");
}

// Function to register a user by saving credentials to a file
int register_user() {
    struct credential user;
    struct userDetails udetail;
    struct acbalance ubal;
    struct transHistory utrans;
    struct feedback ufeed;
    struct loan uloan;
    char path[PATH_LEN],userDir[DIR_LEN];

    //Input credentials
    printf("Register\n");
    printf("Enter UID: ");
    scanf("%d",&user.UID);
    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);
    getchar();

    //Input User details
    printf("Enter Name: ");
    fgets(udetail.name, sizeof(udetail.name), stdin);
    udetail.name[strcspn(udetail.name, "\n")] = 0;

    printf("Enter Email: ");
    fgets(udetail.email, sizeof(udetail.email), stdin);
    udetail.email[strcspn(udetail.email, "\n")] = 0;

    printf("Enter phone: ");
    fgets(udetail.phone, sizeof(udetail.phone), stdin);
    udetail.phone[strcspn(udetail.phone, "\n")] = 0;

    udetail.UID = user.UID;

    //User bank balance Intialize
    ubal.balance = 0;

    //User loan entry
    uloan.loanID=0;
    uloan.loanCount=0;
    uloan.approved=0;
    uloan.rejected=0;
    uloan.pending=0;

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
    bzero(userDir,DIR_LEN);
    snprintf(userDir, PATH_LEN, "%d", user.UID);
    snprintf(path,PATH_LEN,"%s",userDir);
    mkdir(path,0766);


    //Creating User detail File
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%s/userdetail.dat",userDir);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> files",path);
    write(fd,&udetail,sizeof(struct userDetails));
    close(fd);

    //Creating User File for account balance
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%s/balance.dat",userDir);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> files",path);
    write(fd,&ubal,sizeof(struct acbalance));
    close(fd);

    //Creating User Transaction History file
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%s/transactionHist.dat",userDir);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
    close(fd);

    //Creating User Feedback File
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%s/feedback.dat",userDir);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
    close(fd);

    //Creating User Loan detail file
    bzero(path,PATH_LEN);
    snprintf(path,PATH_LEN,"%s/userloandetail.dat",userDir);

    fd = open(path,O_WRONLY|O_CREAT,0766);
    if(fd<0) fprintf(stderr,"Error creating <%s> file",path);
    write(fd,&uloan,sizeof(struct loan));
    close(fd);    
    return 1;
}

int login(char uname[MAX_LEN],char upwd[MAX_LEN]) {
    struct credential file_user;

    int fd = open("credentials.dat", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 0;
    }

    while (read(fd, &file_user, sizeof(struct credential)) > 0) {
        if (strcmp(uname, file_user.username) == 0 &&
            strcmp(upwd, file_user.password) == 0) {
            close(fd);
            return file_user.UID;
        }
    }

    close(fd);
    return 0;
}

void printUserdetail(int userID){
    char path[PATH_LEN];
    struct userDetails userstat;

    snprintf(path,PATH_LEN,"%d/userdetail.dat",userID);
    int fd = open(path,O_RDONLY);
    read(fd,&userstat,sizeof(struct userDetails));
    close(fd);
    printf("User Information-----------------------------\n");
    printf("|Your ID: %d\n|Name: %s\n|Email: %s\n|Phone: %s",userstat.UID,userstat.name,userstat.email,userstat.phone);
}

void printCredFile(){
    char path[]="credentials.dat";
    struct credential user;

    int fd = open(path,O_RDONLY);
    printf("Fetched Data--------------------------\n");
    while(read(fd,&user,sizeof(struct credential))>0){
        printf("%d\t%s\t%s\n",user.UID,user.username,user.password);
    }
    close(fd);
    return;
}

/*
int main() {
    int choice, auth;
    
    while (1) {
        printf("1. Register\n2. Login\n3. change password\n4. Exit\n5. Get user detail\n6. Fetch Credential Data\n7. Delete User\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                char s1[MAX_LEN],s2[MAX_LEN];
                printf("Enter Username: ");
                scanf("%s",s1);
                printf("Enter Password: ");
                scanf("%s",s2);
                auth = login(s1,s2);
                if (auth) {
                    printf("Login successful!\n");
                } else {
                    printf("Login failed. Invalid credentials.\n");
                }
                break;
            case 3:
                char inp1[MAX_LEN],inp2[MAX_LEN],inp3[MAX_LEN];
                printf("Enter your username: ");
                scanf("%s", inp1);
                
                printf("Enter your current password: ");
                scanf("%s",inp2);
                
                printf("Enter new password: ");
                scanf("%s",inp3);
                change_password(inp1,inp2,inp3);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            case 5:
                int id;
                printf("Enter User ID: ");
                scanf("%d",&id);
                printUserdetail(id);
                break;
            case 6:
                printCredFile();
                break;
            case 7:
                char u1[MAX_LEN],u2[MAX_LEN];
                printf("Enter Username: ");
                scanf("%s",u1);
                printf("Enter Password: ");
                scanf("%s",u2);
                deleterecord(u1,u2);
                break;                
            default:
                printf("Invalid choice.\n");
        }

        sleep(1);  // Pause for a moment
    }

    return 0;
}
*/