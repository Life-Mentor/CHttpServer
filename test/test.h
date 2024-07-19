#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *FileName;
  char *path;
  size_t BodySize;
  char *HtmlBody;
} HTMLData;

HTMLData *InitHTML(char *path);


