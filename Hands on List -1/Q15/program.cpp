#include<iostream>
extern char **environ;

int main(void){
  char **env = environ;
  while(*env!=nullptr){
    std::cout << *env++ << std::endl; 
  }
  
  return 0;
}
