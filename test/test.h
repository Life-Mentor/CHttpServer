#include <stdio.h>
#include <stdlib.h>
#include <pcre.h>

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

HTMLData *InitHTML(char *path);
void ParseRouter(Router *routers, char *url, int size);
void TempleteReplace(HTMLData *html);

