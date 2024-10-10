#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      
#include <unistd.h>     
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_LEN 64
#define PATH_LEN 16


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
    int transID;
    int toID;
    char type[MAX_LEN];
    long int balance;
    char date[MAX_LEN];
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
// Function to register a user by saving credentials to a file
int register_user() {
    struct credential user;
    struct userDetails udetail;
    struct acbalance ubal;
    struct transHistory utrans;
    struct feedback ufeed;
    struct loan uloan;
    char path[PATH_LEN],userDir[PATH_LEN];

    //Input credentials
    printf("Register\n");
    printf("Enter UID: ");
    scanf("%d",user.UID);
    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);

    //Input User details
    udetail.UID = user.UID;
    printf("Enter Name: ");
    scanf("%s",udetail.name);
    printf("Enter Email: ");
    scanf("%s",udetail.email);
    printf("Enter phone: ",udetail.phone);

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
    bzero(userDir,PATH_LEN);
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
