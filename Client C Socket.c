#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int valread;

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // declare IP server
    if(inet_pton(AF_INET,"192.168.37.128",&serv_addr.sin_addr)<=0){
      perror("Invalid address/ Address not supported");
      return -1;
     }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // Receive the random number from 0-99
    valread = read(sockfd, buffer, 1024);

if (valread < 0) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }
// Ensure buffer is null-terminated
    buffer[valread] = '\0';

    // Display the random number
    printf("Random number from server: %s\n", buffer);

    // Close the socket
    close(sockfd);
    return 0;
}
