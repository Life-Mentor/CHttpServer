#include "./test.h"
#include "../utils/Utlis.h"
#include <stdio.h>

HTMLData *InitHTML(char *path)
{
  HTMLData *data;
  FILE *HtmlFd = fopen(path, "r");
  if (NULL == HtmlFd) {
    die("HtmlData");
  }

  fseek(HtmlFd, 0, SEEK_END);
  int len = ftell(HtmlFd);
  char *buff = (char *)malloc(sizeof(char) * len + 10);
  fgets(buff, len, HtmlFd);
  printf("%d':'%s\n",len,buff);

  fclose(HtmlFd);
  return data;
}
