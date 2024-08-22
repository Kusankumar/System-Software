#include<stdio.h>
#include<unistd.h>

int main(void){
	int hardLink = link("hardtest.txt","hardlinksys");
	if(hardLink ==-1){
		perror("HardLink");
		return 1;
	}
	return 0;
}
