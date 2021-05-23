#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> // struct 
#include<stdlib.h> //exit()
#include<unistd.h>  //read() and write()
#include<string.h>  //memset

void error(const char *msg){
  
  printf("Error: %s\n",msg);
  exit(1);
}

#define SERVER_PORT 12345


int main(void){

    /* Create  socket */
  
  printf("Creating a socket...\n");
  
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0){
   error("Socket could not be created\n");   
 }
 
 printf("Socket created successfully\n");
 
 
    /* Bind */
 struct sockaddr_in serv_addr;
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(SERVER_PORT);
 
 printf("Address created\n");
 
 
 int br = bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
 
 if(br<0){
  error("Bind failed\n");
}

printf("Bind successful\n");
    /* Listen for incoming connections */


listen(sockfd,5);
printf("Listening for client requests\n");



  /* Accept */
while(1){
  
  struct sockaddr_in clientaddr;
  int caddrlen = sizeof(clientaddr);
  int clienfd = accept(sockfd,(struct sockaddr *)&clientaddr,(socklen_t*)&caddrlen);
  
  
  if(clienfd<0){
    error("Could not accept request for connection\n");
  }
  printf("Connection established\n");
  int pid= fork();
  
  if(pid==0){  
  
    /* Read and Write */
    
    char buffer[100];
    memset(buffer,0,100);
    
    strncpy(buffer,"Hello from Server\n", strlen("Hello from Server\n"));
    int s = write(clienfd,buffer,100);
    if(s<0){
      error("failed writing to client\n");
    }
    printf("Write successful\n");
    
    close(clienfd);
    
  }
}
close(sockfd);
}
