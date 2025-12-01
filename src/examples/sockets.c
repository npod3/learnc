// Purpose: Minimal TCP client (fetch HTTP first line).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif
int example_sockets(void){
#ifdef _WIN32
    WSADATA w; WSAStartup(MAKEWORD(2,2), &w);
#endif
    const char* host="example.org"; const char* port="80";
    struct addrinfo hints; memset(&hints,0,sizeof(hints)); hints.ai_socktype=SOCK_STREAM; hints.ai_family=AF_UNSPEC;
    struct addrinfo*res=0; if(getaddrinfo(host,port,&hints,&res)!=0){ perror("getaddrinfo"); return 1; }
    int sock=(int)socket(res->ai_family,res->ai_socktype,res->ai_protocol); if(sock<0){ perror("socket"); freeaddrinfo(res); return 1; }
    if(connect(sock,res->ai_addr,(int)res->ai_addrlen)<0){ perror("connect"); freeaddrinfo(res);
#ifdef _WIN32
    closesocket(sock); WSACleanup();
#else
    close(sock);
#endif
    return 1; }
    freeaddrinfo(res);
    const char* req="GET / HTTP/1.1\r\nHost: example.org\r\nConnection: close\r\n\r\n";
#ifdef _WIN32
    send(sock, req, (int)strlen(req), 0);
    char buf[512]; int r=recv(sock, buf, sizeof(buf)-1, 0);
    if(r>0){ buf[r]=0; char*nl=strchr(buf,'\n'); if(nl){ *nl=0; } printf("First line: %s\n", buf); }
    closesocket(sock); WSACleanup();
#else
    write(sock, req, strlen(req)); char buf[512]; int r=(int)read(sock, buf, sizeof(buf)-1);
    if(r>0){ buf[r]=0; char*nl=strchr(buf,'\n'); if(nl){ *nl=0; } printf("First line: %s\n", buf); }
    close(sock);
#endif
    return 0; }
