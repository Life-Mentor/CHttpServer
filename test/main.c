#include "./test.h"
#include <stdio.h>

void hello() { printf("hello\n"); }
void h() { printf("hello\n"); }
void duck() { printf("duck\n"); }

Router routers[] = {
    {"/hello", "da", hello, "hello"}, {"/duck", "djsk", duck, "duck"},
    {"/duck", "djsk", h, "duck"},     {"/duck", "djsk", h, "duck"},
    {"/duck", "djsk", h, "duck"},     {"/duck", "djsk", h, "duck"},
};
int main() {
  int size = sizeof(routers) / sizeof(routers[0]);
  ParseRouter(routers,"/duck",size);
  return EXIT_SUCCESS;
}
