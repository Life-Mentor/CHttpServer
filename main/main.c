#include "../http/MapperApi.h"
#include "../utils/Utlis.h"

void hello(char *path);
void init();

Router routers[] = {
    { "/hello","/home/duck/ACODE/C/My_Probjects/C_Http_Server/test/test.html", hello, "hello"},
};

int main(int argc, char *argv[]) {
  init();
  return EXIT_SUCCESS;
}

void init() {
  HttpMapper *HTTP;
  if (InitServer(HTTP, "127.0.0.1", 1232) != 0) {
    die("HttpError");
  }

  if (StartServer(HTTP) != 0) {
    CloseServer(HTTP);
    die("StartServer\n");
  }

  CloseServer(HTTP);
}
void hello(char *path)
{
    printf("hello world\n");
}
