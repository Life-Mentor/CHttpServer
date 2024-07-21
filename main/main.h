#ifndef __MAIN__
#define __MAIN__

#include "../http/MapperApi.h"
#include "../utils/Utlis.h"

// HTMLData *hello(char *path);
extern Router routers[];
extern const int router_count;
HTMLData *hello(char *path);


#endif // !__MAIN__
