/*
    C socket server example
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // strlen
#include <sys/socket.h>  // socket
#include <arpa/inet.h>   // inet_addr
#include <unistd.h>      // write



int main(int argc , char *argv[])
{
    // Variables
    int ssock, csock, addrlen, read_size;
    struct sockaddr_in server, client;
    char hold[20];

    short port = 8888;

    // Create a socket. Return value is a file descriptor for the socket.
    ssock = socket(AF_INET, SOCK_STREAM, 0);
    if (ssock == -1) {
        perror("Error creating socket\n");
        exit(0);
    }
    printf("Server socket created\n");

    // Set the server ip address, connection family and port. INADDR_ANY means
    // all the ip addresses of the server can be used to set up connection.
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(port);

    // Bind the socket for the connection
    if (bind(ssock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        //print the error message
        perror("Error binding\n");
        close(ssock);
        exit(0);
    }
    printf("Binding done\n");

    // Listen for incoming connections
    listen(ssock, SOMAXCONN);
    printf("Listening...\n");

    printf("Waiting for incoming connections...\n");
    addrlen = sizeof(struct sockaddr_in);

    // Accept connection from an incoming client
    csock = accept(ssock, (struct sockaddr *) &client, (socklen_t *) &addrlen);
    if (csock < 0) {
        perror("Error accepting connections\n");
        exit(0);
    }
    printf("Connection accepted\n");

while(1){
    memset(hold, 0, sizeof(hold));
    // Receive a message from the client. recv() is an alternative for read().
    // Similarly, send() can replace write().
    if ((read_size = read(csock, hold, sizeof(hold))) > 0) {
        printf("%s ", hold);
    fflush(stdout);
    } else {
        perror("Error receiving\n");
    }

}
    close(csock);
    close(ssock);
    printf("End connection\n");

    return 0;
}