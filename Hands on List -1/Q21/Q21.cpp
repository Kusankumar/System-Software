#include<iostream>
#include<unistd.h>
#include<cstring>
#include<cerrno>

int main(){
        pid_t cid = fork();
	if(cid==-1){
		std::cout << "Some problem occur: " << std::strerror(errno) << std::endl;
		return 1;
	}
	else if(cid == 0){
		std::cout << "Parent ProcessID: " << getppid() << "  Child ProcessID: " << getpid() << std::endl;
	}
	if(cid!=0)
                std::cout << "Parent ProcessID: " << getpid() << "  Child ProcessID: " << cid << std::endl;
	return 0;
}

