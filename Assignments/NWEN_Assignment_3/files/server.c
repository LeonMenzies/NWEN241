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
#define MAX 1000

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
            printf("Client connected\n");
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

    //Fields
    int write_to_file = 0;
    FILE *to_send;
    FILE *to_write;

    //infinite loop for chatting
    while (1)
    {
        bzero(buffer, MAX);

        /* 5. Read messages from the client*/
        read(sock, buffer, sizeof(buffer));
        printf("From client: %s", buffer);

        //if files should be written to the file
        if (write_to_file == 1)
        {
            for (int i = 0; i < strlen(buffer); i++)
            {
                if (strlen(buffer) == 1 & buffer[i] == '\n')
                {
                    write_to_file = 0;
                    fclose(to_write);
                    break;
                }
                fputc(buffer[i], to_write);
            }
        }

        /* 6.a.b Perform taks depending on the input from the client*/
        if (strncmp("BYE", buffer, 3) == 0)
        {
            printf("Closing server\n");
            return;
        }
        else if (strncmp("GET", buffer, 3) == 0)
        {

            char c;
            int count = 0;
            char file_name[MAX];

            //Iterate from from the start of the filename
            for (int i = 0; i < strlen(buffer); i++)
            {
                file_name[i] = buffer[i + 4];
            }
            //Set filename as a string
            file_name[strlen(file_name) - 1] = '\0';
            bzero(buffer, MAX);

            //Open the file or send an error if the input is incorrect
            to_send = fopen(file_name, "r");
            if (strlen(file_name) == 0)
            {
                strcat(buffer, "SERVER 500 Not Found\n");
            }
            else if (to_send == NULL)
            {
                strcat(buffer, "SERVER 404 Not Found\n");
            }
            else
            {
                strcat(buffer, "SERVER 200 OK\n\n");

                //Copy the content of the file into the buffer
                int count_to_send = strlen(buffer);
                while ((c = fgetc(to_send)) != EOF)
                {
                    buffer[count_to_send] = c;
                    count_to_send++;
                }
                strcat(buffer, "\n\n");
            }
        }
        /* 6.c Write to a file */
        else if (strncmp("PUT", buffer, 3) == 0)
        {
            char c;
            int count = 0;
            char file_write_name[MAX];

            //Iterate from from the start of the filename
            for (int i = 0; i < strlen(buffer); i++)
            {
                file_write_name[i] = buffer[i + 4];
            }
            //Set filename as a string
            file_write_name[strlen(file_write_name) - 1] = '\0';
            bzero(buffer, MAX);

            //Open the file for writing or send an error if the input is incorrect
            to_write = fopen(file_write_name, "w");
            if (to_write == NULL)
            {
                strcat(buffer, "SERVER 501 Put Error\n");
            }
            else
            {
                write_to_file = 1;
            }
        }
        //Clear the buffer
        else
        {
            bzero(buffer, MAX);
        }

        //Write to client
        write(sock, buffer, sizeof(buffer));
    }
}