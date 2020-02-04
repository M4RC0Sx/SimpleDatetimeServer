
#include <stdio.h>
#include <time.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/types.h> 


#define ERROR 1
#define STRING_SIZE 1024

#define PORT 12000

#define MAX_CONNECTIONS 5


// Function designed for chat between client and server. 
void send_date(int sockfd) 
{ 
    char date_string[STRING_SIZE] = " "; 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Date format = %d/%m/%Y - %H:%M:%S

    // Format date string.
    sprintf(date_string, "%02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // Send formatted string to client.
    write(sockfd, date_string, sizeof(date_string)); 

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
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept any addresses.
    server.sin_port = htons(PORT); 
  
    // Bind socket.
    if((bind(socket_val, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        printf("[SimpleDatetimeServer/ERROR] Could not bind socket.\n"); 
        exit(ERROR); 
    }
  
    // Listen to MAX_CONNECTIONS.
    if((listen(socket_val, MAX_CONNECTIONS)) != 0) { 
        printf("[SimpleDatetimeServer/ERROR] Could not listen.\n"); 
        exit(ERROR); 
    } 
  
    // Accept packets from client.
    len = sizeof(client); 

    conn = accept(socket_val, (struct sockaddr*)&client, &len); 
    if(conn < 0) { 
        printf("[SimpleDatetimeServer/ERROR] Could not accept packets from client.\n"); 
        exit(ERROR); 
    }
  
    // Function to send the date to the client.
    send_date(conn); 
  
    // Close the socket when process is finished.
    close(socket_val); 
}
