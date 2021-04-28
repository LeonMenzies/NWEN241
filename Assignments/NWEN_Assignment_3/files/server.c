/**
 * Skeleton file for server.c
 * 
 * You are free to modify this file to implement the server specifications
 * as detailed in Assignment 3 handout.
 * 
 * As a matter of good programming habit, you should break up your imple-
 * mentation into functions. All these functions should contained in this
 * file as you are only allowed to submit this file.
 */

#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // struct
#include <stdlib.h>     //exit()
#include <unistd.h>     //read() and write()
#include <string.h>     //memset
// Include necessary header files

//Constants
#define MAX 100

/**
 * The main function should be able to accept a command-line argument
 * argv[0]: program name
 * argv[1]: port number
 * 
 * Read the assignment handout for more details about the server program
 * design specifications.
 */
void read_write(int sock);
void error(const char *msg)
{
    printf("Error: %s\n", msg);
    exit(1);
}

int main(int argc, char *argv[])
{

    /* 1. Check for correct arguments*/
    if (argc != 2)
    {
        error("Incorrect amount of arguments\n");
    }

    /* 1. Check the port number is valid*/
    int port = atoi(argv[1]);
    if (port > 65536 || port <= 1023)
    {
        error("Invalid port number\n");
        return -1;
    }

    /* 2. Create and bind the socket */
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        error("Socket could not be created\n");
    }
    else
    {
        printf("Socket succesfully created\n");
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    int br = bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (br < 0)
    {
        error("Failed to bind\n");
    }
    else
    {
        printf("Socket succesfully binded\n");
    }

    /* 3. Listen for TCP*/
    while (1)
    {

        int fd = listen(sock, 5);
        if (fd < 0)
        {
            error("Failed to listin\n");
        }
        else
        {
            printf("Server listening\n");
        }

        /* 4. Establish connection*/
        struct sockaddr_in clientaddr;
        int caddrlen = sizeof(clientaddr);

        int clienfd = accept(sock, (struct sockaddr *)&clientaddr, (socklen_t *)&caddrlen);
        if (clienfd < 0)
        {
            error("Could not accept\n");
        }
        else
        {
            printf("Succesfully accept\n");
        }

        /* Function for read/write to client*/
        read_write(clienfd);
        close(clienfd);
    }
    return 0;
}

void read_write(int sock)
{
    /* 4. Send message to client*/
    write(sock, "HELLO\n", sizeof("HELLO\n"));

    //Create a buffer
    char buffer[MAX];

    //infinite loop for chatting
    while (1)
    {
        bzero(buffer, MAX);

        /* 5. Read messages from the client*/
        read(sock, buffer, sizeof(buffer));
        printf("From client: %s\n", buffer);

        /* 6. Perform taks depending on the input from the client*/
        if (strncmp("BYE", buffer, 3) == 0)
        {
            printf("Closing server\n");
            return;
        }

        if (strncmp("GET", buffer, 3) == 0)
        {

            FILE *to_send;
            char c;
            int count = 0;
            char file_name[MAX];

            //Iterate from from the start of the filename
            for (int i = 0; i < MAX; i++)
            {
                char buffer_c = buffer[i + 4];
                if (buffer_c == '\0')
                {
                    break;
                }
                file_name[i] = c;
            }

            printf("File Name: ||%s||\n ", file_name);

            to_send = fopen(file_name, "r");
            if (sizeof(file_name) == 0)
            {
                strcat(buffer, "SERVER 500 Not Found\n");
            }
            else if (to_send == NULL)
            {
                strcat(buffer, "SERVER 404 Not Found\n");
            }

            else
            {
                int count_to_send = 0;
                while ((c = fgetc(to_send)) != EOF)
                {
                    buffer[count_to_send] = c;
                    count_to_send++;
                }
                write(sock, buffer, sizeof(c));
            }
        }

        write(sock, buffer, sizeof(buffer));
        bzero(buffer, MAX);
    }
}