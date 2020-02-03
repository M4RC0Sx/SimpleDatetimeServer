
#include <stdio.h>
#include <time.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 


#define ERROR 1
#define STRING_SIZE 1024

#define PORT 12000
#define LOCALHOST "127.0.0.1"

#define MAX_CONNECTIONS 5


void read_date(int sockfd)
{
    char date_string[STRING_SIZE];

    read(sockfd, date_string, sizeof(date_string)); 
    printf("[SimpleDatetimeServer/INFO] Current datetime sent by client: %s", date_string); 

    return;
}

// Main server function.
int main() 
{ 
    int socket_val, conn, len; 
    struct sockaddr_in server, client;
  
    // Socket creation.
    socket_val = socket(AF_INET, SOCK_STREAM, 0); 
    if(socket_val < 0) { 
        printf("[SimpleDatetimeServer/ERROR] Could not create socket.\n"); 
        exit(ERROR); 
    }

    // Assign direction IP and PORT.
    bzero(&server, sizeof(server)); 
  
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = inet_addr(LOCALHOST);  // Localhost client.
    server.sin_port = htons(PORT); 
  
    // Connect to server socket.
    if((connect(socket_val, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        printf("[SimpleDatetimeServer/ERROR] Could not connect to server socket.\n"); 
        exit(ERROR); 
    }

    printf("[SimpleDatetimeServer/INFO] Connected to server.\n");

    // Function to read the date from the server.
    read_date(socket_val); 

    // Close the socket when process is finished.
    close(socket_val); 
}
