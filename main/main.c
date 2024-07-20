#include "./main.h"

Router routers[] = {
    { "/hello","/home/duck/ACODE/C/My_Probjects/C_Http_Server/test/test.html", hello, "hello"},
};
const int router_count = sizeof(routers) / sizeof(routers[0]);
int main(int argc, char *argv[]) {
  HttpMapper *HTTP;
  if (InitServer(HTTP, "127.0.0.1", 1232) != 0) {
    die("HttpError");
  }

  if (StartServer(HTTP) != 0) {
    CloseServer(HTTP);
    die("StartServer\n");
  }

  CloseServer(HTTP);
  return EXIT_SUCCESS;
}
void hello(char *path)
{
    printf("hello world\n");
}
