#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<cstring>
#include<ctime>

int main(){
	const char *path = "program.cpp";//can't give same file path, BAD address
	struct stat buffer;

	if(stat(path,&buffer)<0){
		perror("Retrieving File Information Failed");
		return 1;
	}
	printf("File Information for %s-----------\n",path);
	std::cout <<"iNode: " << buffer.st_ino << std::endl;
	std::cout <<"No of HardLink: " << buffer.st_nlink << std::endl;
	std::cout <<"uid: " << buffer.st_uid << std::endl;
	std::cout <<"gid: " << buffer.st_gid << std::endl;
	std::cout <<"size: " << (buffer.st_size)/1024.0 << std::endl;
	std::cout <<"block size: " << (buffer.st_blksize)/1024.0 << std::endl;
	std::cout <<"number of blocks: " << buffer.st_blocks << std::endl;
	std::cout <<"time of last access: " << ctime(&buffer.st_atime) << std::endl;
	std::cout <<"time of last modification: " << ctime(&buffer.st_mtime) << std::endl;
	std::cout <<"time of last change: " << ctime(&buffer.st_ctime) << std::endl;
	return 0;
}
/*
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change

*/
