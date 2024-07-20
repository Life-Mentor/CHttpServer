#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../main/main.h"
#include "MapperApi.h"

#define RESPONSE_TEMPLATE_404                                                  \
  "HTTP/1.1 200 OK\r\n"                                                        \
  "Content-Type: text/html\r\n"                                                \
  "Content-Length: %zu\r\n"                                                    \
  "\r\n"                                                                       \
  "<h1>404 Error"
#define RESPONSE_TEMPLATE_200                                                  \
  "HTTP/1.1 200 OK\r\n"                                                        \
  "Content-Type: text/html\r\n"                                                \
  "Content-Length: %zu\r\n"                                                    \
  "\r\n"                                                                       \
  "%s"

int InitServer(HttpMapper *hm, char *ip, int prot) {
  hm->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (hm->server_fd < 0) {
    die("SocketError\n");
  }
  hm->server_addrs.sin_addr.s_addr = inet_addr(ip);
  hm->server_addrs.sin_family = AF_INET;
  hm->server_addrs.sin_port = htons(prot);

  return 0;
}
int StartServer(HttpMapper *sm) {
  if (bind(sm->server_fd, (struct sockaddr *)&sm->server_addrs,
           sizeof(sm->server_addrs)) < 0) {
    die("BindError\n");
  }
  if (listen(sm->server_fd, 5) < 0) {
    die("ListenError\n");
  }
  socklen_t SM_len = sizeof(sm->server_addrs);
  while (1) {
    int acceptFd =
        accept(sm->server_fd, (struct sockaddr *)&sm->server_addrs, &SM_len);
    if (acceptFd < 0) {
      die("AcceptError\n");
      return -1;
    }
    HandleNetworkRequests(acceptFd);
    close(acceptFd);
  }
  return 0;
}
int HandleNetworkRequests(int AcceptFd) {
  ResponseBuffer buffer;
  CreateBuffer(&buffer, 1024);
  read(AcceptFd, buffer.data, buffer.size);
  char *url = GetUrl(buffer.data);
  Router OkRouter = ParseRouter(routers, url, router_count);
  if (NULL == OkRouter.url) {
    send(AcceptFd, RESPONSE_TEMPLATE_404, sizeof(RESPONSE_TEMPLATE_404), 0);
  } else {
    HTMLData *data = OkRouter.Callback(OkRouter.path);
    if (data) {
      char *response = (char *)malloc(
          sizeof(char) * (data->BodySize + strlen(RESPONSE_TEMPLATE_200)));
      if (response) {
        snprintf(response, data->BodySize + strlen(RESPONSE_TEMPLATE_200),
                 RESPONSE_TEMPLATE_200, data->BodySize, data->HtmlBody);
        send(AcceptFd, response, strlen(response), 0);
        free(response);
      }
    }
    send(AcceptFd, data->HtmlBody, data->BodySize, 0);
    free(data->HtmlBody);
    free(data);
  }

  return 0;
}
int CloseServer(HttpMapper *server) {
  close(server->server_fd);
  return 0;
}

char *GetUrl(char *ResponseBuffer) {
  strtok(ResponseBuffer, " ");
  char *p = strtok(NULL, " ");
  return p;
}

HTMLData *InitHTML(char *path) {
  HTMLData *data = (HTMLData *)malloc(sizeof(HTMLData));
  if (NULL == data) {
    die("HTMLDataError:");
  }

  data->path = path;
  data->FileName = path;

  FILE *HtmlFd = fopen(path, "r");
  if (NULL == HtmlFd) {
    free(data);
    die("HtmlData");
  }

  fseek(HtmlFd, 0, SEEK_END);
  int len = ftell(HtmlFd);
  fseek(HtmlFd, 0, SEEK_SET);

  data->HtmlBody = (char *)malloc(sizeof(char) * (len + 1));
  if (data->HtmlBody == NULL) {
    fclose(HtmlFd);
    free(data);
    die("Memory allocation error for HtmlBody");
  }

  fread(data->HtmlBody, sizeof(char), len, HtmlFd);
  data->HtmlBody[len] = '\0';
  data->BodySize = len;
  fclose(HtmlFd);
  return data;
}

Router ParseRouter(Router *routers, char *url, int size) {
  for (int i = 0; i < size; i++) {
    if (routers[i].url != NULL && url != NULL &&
        strcmp(routers[i].url, url) == 0) {
      return routers[i];
    }
  }
  Router NullRouter = {NULL, NULL, NULL, NULL};
  return NullRouter;
}
