#include "./test.h"

int main()
{
  HTMLData *data = InitHTML("/home/duck/CODE/CHttpServer/test/test.html");
  printf("File content:\n%s\n", data->HtmlBody);
  free(data->HtmlBody);
  free(data);
  return EXIT_SUCCESS;
}

