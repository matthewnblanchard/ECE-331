/* Matthew Blanchard
 * ECE 331
 * 4/16/2017
 * client.c
 *      Adapted from Robert Ingalls source code:
 *      www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
 *      Fetches a webpage at target hostname/port
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int port = 0;                   // Port number
        int sockfd = 0;                 // Socket file descriptor
        struct sockaddr_in serv_addr;   // Internet address struct
        struct hostent *server;         // Internet host
        char buffer[2048];              // Write/read buffer
        char *request =                 // HTTP request string
              "GET /index.html HTTP/1.1\r\nhost: thetraveler\r\n\r\n";  
        int req_len = strlen(request);  // Length of request string

        // Should receive two arguments: host and port
        if (argc != 3) {
                printf("Error: expected two arguments, found %d\n ...", argc - 1);
                return 1;
        }

        // Convert port argument to integer
        port = atoi(argv[2]);
        if (port <= 0) {
                printf("Error: %s is not a valid port ... \n", argv[2]);
                return 2;
        }

        // Open stream socket (TCP) over internet
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
                printf("Error: failed to open socket ... \n");
                return 3;
        }

        // Read host argument
        server = gethostbyname(argv[1]);
        if (server == NULL) {
                printf("Error: host %s not found ... \n", argv[1]);
                return 4;
        }

        // Clear internet address
        bzero((char *)&serv_addr, sizeof(serv_addr));
        
        // Set up server info
        serv_addr.sin_family = AF_INET; // Address type is internet
        bcopy((char *)server->h_addr,   // Copy server IP address 
              (char *)&serv_addr.sin_addr.s_addr, 
              server->h_length);
        serv_addr.sin_port = htons(port); // Copy server port in network byte order

        // Connect to server
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
                printf("Error: failed to connect to server ... \n");
                return 5;
        }
        
        // Write HTTP request
        if (write(sockfd, request, req_len) < 0) {
                printf("Error: failed to write HTTP request ... \n");
                return 6;
        }        

        // Read HTTP response
        bzero(buffer, 2048);                    // Clear buffer
        while (read(sockfd, buffer, 2047)) {    // Read response and print until it's finished
                printf("%s", buffer);
                bzero(buffer, 2048);            
        }

        return 0;
}
