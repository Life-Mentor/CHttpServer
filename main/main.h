#include "../http/MapperApi.h"
#include "../utils/Utlis.h"

int hello();

Router routers[] = {
    { "/hello", hello, "hello"},
};

