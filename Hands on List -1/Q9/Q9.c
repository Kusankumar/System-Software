/*
============================================================================
Name : Q9.c
Author : Sonu Kumar Mahto

Description--------------------------
9. Write a program to print the following information about a given file.
a. inode
b. number of hard links...

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<time.h>

int main(){
	const char *path = "program.cpp";//can't give same file path, BAD address
	struct stat buffer;

	if(stat(path,&buffer)<0){
		perror("Retrieving File Information Failed");
		return 1;
	}
	printf("File Information for %s-----------\n",path);
	printf("iNode: %lu\n", buffer.st_ino);
    printf("No of HardLink: %lu\n", buffer.st_nlink);
    printf("uid: %u\n", buffer.st_uid);
    printf("gid: %u\n", buffer.st_gid);
    printf("size: %.2f KB\n", buffer.st_size / 1024.0);
    printf("block size: %.2f KB\n", buffer.st_blksize / 1024.0);
    printf("number of blocks: %lu\n", buffer.st_blocks);
    printf("time of last access: %s", ctime(&buffer.st_atime));
    printf("time of last modification: %s", ctime(&buffer.st_mtime));
    printf("time of last change: %s", ctime(&buffer.st_ctime));
	return 0;
}
/*
$ ./main
File Information for program.cpp-----------
iNode: 3020251
No of HardLink: 1
uid: 1000
gid: 1000
size: 1.17 KB
block size: 4.00 KB
number of blocks: 8
time of last access: Sat Aug 31 16:58:31 2024
time of last modification: Fri Aug 23 20:47:48 2024
time of last change: Fri Aug 23 20:47:48 2024

*/
