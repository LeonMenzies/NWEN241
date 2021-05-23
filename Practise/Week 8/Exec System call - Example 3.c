#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
 
   int main()
   {       
       if( execl("/bin/ls","ls",NULL) == -1){         
         printf("Exec failed");
       }
       printf("Success\n");
       return 0;
   }
