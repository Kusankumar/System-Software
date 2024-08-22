#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>
int main(void){
	char *path = "testfile.txt";
	int fd = creat(path,0666);

	if(fd==-1){
		perror("File creation failed: ");
		return 1;
	}
	char data[100];
	fgets(data, 100, stdin);
	ssize_t wfd = write(fd,data,strlen(data));
	if(wfd<0){
		perror("can't write: ");
		return -1;
	}
	printf("FileDescriptor: %d\nFile written successfully \n",fd);
	close(fd);
	return 0;
}
/*
ssize_t: This type is specifically defined for functions like write() and read() to represent sizes.
It is part of the POSIX standard and is designed to handle the maximum possible size of objects that
a system can manage. Its size can vary depending on the architecture.

int: The int type has a fixed size (typically 32 bits on most systems), which might not be sufficient
to represent very large sizes on some platforms, especially on 64-bit systems where ssize_t could be 
64 bits wide
*/
