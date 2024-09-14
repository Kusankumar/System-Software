#include<stdio.h>
#include<unistd.h>

int main(void) {
	int softLink = symlink("test.txt","softlinksys.txt");
	if(softLink==-1){
		perror("SoftLink: ");
		return 1;
	}
	return 0;
}
