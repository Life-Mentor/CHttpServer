#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MapperApi.h"
#include "../utils/Utlis.h"
  
char *response = "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/html\r\n"
      "Content-Length: %zu\r\n"
      "\r\n"
      "%s";

int InitServer(HttpMapper *hm, char *ip, int prot)
{
    hm->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (hm->server_fd < 0)
    {
        die("SocketError\n");
    }
    hm->server_addrs.sin_addr.s_addr = inet_addr(ip);
    hm->server_addrs.sin_family = AF_INET;
    hm->server_addrs.sin_port = htons(prot);

    return 0;
}
int StartServer(HttpMapper *sm)
{
    // printf("OK Start\n");
    if (bind(sm->server_fd, (struct sockaddr *)&sm->server_addrs, sizeof(sm->server_addrs)) < 0) {
        die("BindError\n");
    }
    if (listen(sm->server_fd, 5) < 0) {
        die("ListenError\n");
    }
    socklen_t SM_len = sizeof(sm->server_addrs);
    while (1) {
        int acceptFd = accept(sm->server_fd, (struct sockaddr *)&sm->server_addrs, &SM_len);
        if (acceptFd < 0) {
            die("AcceptError\n");
            return -1;
        }
        HandleNetworkRequests(acceptFd);
        close(acceptFd);
    }
    return 0;
}
int HandleNetworkRequests(int AcceptFd)
{
    ResponseBuffer buffer;
    CreateBuffer(&buffer, 1024);
    read(AcceptFd,buffer.data,buffer.size);
    char *url = GetUrl(buffer.data);
    printf("URL:%s\n",url);
    free(buffer.data);

    char text[1024];
    send(AcceptFd,text,1024,0);

    return 0;
}
int CloseServer(HttpMapper *server)
{
    // printf("OK CloseServer\n");
    close(server->server_fd);
    return 0;
}

char *GetUrl(char *ResponseBuffer)
{
    // printf("%s\n",ResponseBuffer);
    strtok(ResponseBuffer, " ");
    char *p = strtok(NULL, " ");
    return p;
}


HTMLData *InitHTML(size_t BodySize, char path)
{
  HTMLData *data;

  FILE *HtmlFd = fopen(&path, "r");
  if (NULL == HtmlFd) {
    printf("HtmlFileNo\n");
    die("HtmlFileError\n");
  }


  return data;
}




