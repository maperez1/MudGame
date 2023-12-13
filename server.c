// Compile with gcc server.c -o server -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

#define PORT 12345
#define BUFFER_SIZE 256

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void *handle_client(void *client_socket) {
    int sock = *(int*)client_socket;
    char buffer[BUFFER_SIZE];
    int n;

    // Read the message from the client
    memset(buffer, 0, BUFFER_SIZE);
    n = read(sock, buffer, BUFFER_SIZE - 1);
    if (n < 0) error("ERROR reading from socket");

    printf("Here is the message: %s\n", buffer);

    // Respond to the client
    n = write(sock, "I got your message", 18);
    if (n < 0) error("ERROR writing to socket");

    close(sock);
    return 0;
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    int n, *new_sock;
    pthread_t server_thread;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    printf("Server started on port %d\n", PORT);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
              error("ERROR on accept");

        new_sock = malloc(1);
        *new_sock = newsockfd;

        if (pthread_create(&server_thread, NULL, handle_client, (void*) new_sock) < 0) {
            error("ERROR creating thread");
        }
        
        // Now join the thread, so that we don't terminate before the thread
        pthread_join(server_thread , NULL);
    }

    close(sockfd);
    return 0; 
}
