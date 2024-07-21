#include "./test.h"
#include "../utils/Utlis.h"
#include <pcre.h>
#include <stdio.h>
#include <string.h>

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
  printf("%zu':'%s\n", data->BodySize, data->HtmlBody);

  fclose(HtmlFd);
  return data;
}

void ParseRouter(Router *routers, char *url, int size) {
  for (int i = 0; i < size; i++) {
        if (strcmp(routers[i].url,url) == 0) {
            routers->Callback();
        }
    }
}
void TempleteReplace(HTMLData *html)
{
    pcre *RE;
}










