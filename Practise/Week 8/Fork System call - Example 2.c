#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  int p=10;
  //fork();
  //fork();
  
  fork() && fork();
  printf(" %d\n", p);
    
}
