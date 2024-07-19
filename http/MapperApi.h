#define HTTP_API

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int server_fd;
    struct sockaddr_in server_addrs;
} HttpMapper;
typedef struct {
  char *FileName;
  char *path;
  size_t BodySize;
  char *HtmlBody;
} HTMLData;

typedef struct {
    char *url;
    char *path;
    void (*Callback)();
    char *TagName;
} Router;

int InitServer(HttpMapper *hm, char *ip, int prot);
int StartServer(HttpMapper *sm);
int HandleNetworkRequests(int HttpMapper);
int CloseServer(HttpMapper *server);
char *GetUrl(char *ResponseBuffer);
HTMLData *InitHTML(char *path);
void ParseRouter(Router *routers, char *url, int size);
