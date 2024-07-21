#ifndef HTTP_API
#define HTTP_API

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct {
    int server_fd;
    struct sockaddr_in server_addrs;
} HttpMapper;

typedef struct {
  char *path;
  size_t BodySize;
  char *HtmlBody;
} HTMLData;

typedef struct {
    char *url;
    char *path;
    HTMLData *(*Callback)(char *path);
    char *TagName;
} Router;

// typedef struct { } ;

int InitServer(HttpMapper *hm, char *ip, int prot);
int StartServer(HttpMapper *sm);
int HandleNetworkRequests(int HttpMapper);
int CloseServer(HttpMapper *server);
char *GetUrl(char *ResponseBuffer);
HTMLData *InitHTML(char *path);
Router ParseRouter(Router *routers, char *url, int size);
#endif // !HttpMapper
