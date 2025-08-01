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

int client_socket = socket(AF_INET, SOCK_STREAM,0);
printf("Socket fd = %d\n", client_socket);
if(client_socket == INVALID_SOCKET){
    printf("failed to create socket\n");
    exit(EXIT_FAILURE);
}

struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(7000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int result = connect(client_socket,(struct sockaddr_in*)&server, sizeof(server));
if(result < 0){
    printf("failed to connect to server");
    exit(EXIT_FAILURE);
}
char buffer[1024];

printf("send message:");
fgets(buffer,1024,stdin);
buffer[strcspn(buffer, "\n")] = '\0';
size_t length = strlen(buffer);
int bytes_send = send(client_socket,buffer,sizeof(length) -1,0);
int bytes_read = recv(client_socket, buffer, sizeof(length) - 1, 0);
if (bytes_read > 0) {
    buffer[bytes_read] = '\0';
    printf("client replied: %s", buffer);
   
}
 
    closesocket(client_socket);
    WSACleanup();
getchar();
getchar();
    return 0;
}
