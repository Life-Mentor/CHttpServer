#include "../http/MapperApi.h"
#include "../utils/Utlis.h"

void (hello)(char *path);
void init();

Router routers[] = {
    { "/hello","/home/duck/ACODE/C/My_Probjects/C_Http_Server/test/test.html", hello, "hello"},
};


