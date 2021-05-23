#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // struct
#include <stdlib.h>     //exit()
#include <unistd.h>     //read() and write()
#include <string.h>     //memset

#define SERVER_PORT 23456

int main(void)
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    int br = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(fd, 5);

    struct sockaddr_in clientaddr;
    int caddrlen = sizeof(clientaddr);

    int clienfd = accept(fd, (struct sockaddr *)&clientaddr, (socklen_t *)&caddrlen);

    char in_buffer[100];
    char out_buffer[100];
    memset(in_buffer, 0, 100);
    memset(out_buffer, 0, 100);

    read(clienfd, in_buffer, sizeof(in_buffer));

    int count = 0;
    for (int i = strlen(in_buffer) - 1; i >= 0; i--)
    {
        out_buffer[count] = in_buffer[i];
        count++;
    }

    write(clienfd, out_buffer, sizeof(out_buffer));
    shutdown(clienfd, SHUT_RDWR);
    close(clienfd);
}