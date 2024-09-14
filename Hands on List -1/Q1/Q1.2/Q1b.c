/*
============================================================================
Name : Q1b.c
Author : Sonu Kumar Mahto

Description--------------------------
Create the following types of a files using (i) shell command (ii) system call
b. hard link (link system call)


Date: 30th Aug, 2024.
============================================================================*/

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
/*
i.b---------------------------------------------
$ ln hardtest.txt h1.txt

$ cat h1.txt
Hi there my name is Sonu Kumar Mahto.
I'm student at IIITB persuing my MTech in CSE.

So, here are some updates to test  Hardlink.
Some more update after making hardlink using system call link()

ii.b---------------------------------------------
$ gcc Q1b.c -o Q1b
 
$ cat hardlinksys
Hi there my name is Sonu Kumar Mahto.
I'm student at IIITB persuing my MTech in CSE.

*/

