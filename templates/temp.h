#include "../main/main.h"

typedef struct {
  HTMLData *OriginalHTML;
  HTMLData *ModernHTML;
} Templates;



Templates *CreateTemp(Templates *templates);
void *FindKey(char *key);

