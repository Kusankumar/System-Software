#include<stdio.h>

int main(int argc, char*argv[]){
  if(argc<2){
    printf("Not enough Arguments\n");
    return 1;
  }
  printf("Hi, My name is %s\nTommorow is my %s \n",argv[1],argv[2]);
  return 0;
}
