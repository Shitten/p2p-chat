#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <winsock2.h>     // Main socket API
#include <ws2tcpip.h>     // For modern IP stuff (IPv6, inet_pton, etc.)
#pragma comment(lib, "ws2_32.lib") 

int main(){

	//start for initializing socket
WSADATA wsa;
WSAStartup(MAKEWORD(2,2), &wsa);

int server_socket = socket(AF_INET, SOCK_STREAM,0);
printf("Socket fd = %d\n", server_socket);
if(server_socket == INVALID_SOCKET){
    printf("failed to create socket\n");
    exit(EXIT_FAILURE);
}


 struct sockaddr_in server_addr;
 memset(&server_addr,0,sizeof(server_addr));
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr= htonl(INADDR_ANY);
 server_addr.sin_port = htons(7000);
 int result = bind(server_socket,(struct sockaddr *)&server_addr,sizeof(server_addr));
if(result < 0){
    printf("failed to bind\n");
     closesocket(server_socket); 
    WSACleanup();               //only for windows
    return 1;
};
 	printf("Bind status %d\n",result);
   
   
    if (listen(server_socket, 10) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
}

printf("Listening on port %d",ntohs(server_addr.sin_port));

struct sockaddr_in client_addr;
int addrlen = sizeof(client_addr);
int new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addrlen);
if(new_socket < 0){
    printf("failed to accept clients \n");
    exit(EXIT_FAILURE);  
}else{
    printf("client connected successfully!\n");
}

char buffer[1024];
int bytes_read = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
if (bytes_read > 0) {
    buffer[bytes_read] = '\0';
    printf("client replied: %s", buffer);
   
}
 closesocket(new_socket);
    closesocket(server_socket);
    WSACleanup();
getchar();
getchar();
    return 0;
}
