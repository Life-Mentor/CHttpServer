#include "../http/MapperApi.h"
#include "../utils/Utlis.h"

int main(int argc, char *argv[]) 
{
    HttpMapper *HTTP;
    if( InitServer(HTTP, "127.0.0.1", 1232) != 0) {
        die("HttpError");
    }

    if (StartServer(HTTP) != 0)
    {
        CloseServer(HTTP);
        die("StartServer\n");
    }

    CloseServer(HTTP);

    return EXIT_SUCCESS; 
}
