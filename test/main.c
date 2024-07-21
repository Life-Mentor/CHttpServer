#include "./test.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char buffer[1024];
  char *path = "./main.c";
  if (realpath(path, buffer) != NULL) {
    printf("%s\n", buffer);
  } else {
    perror("Error resolving absolute path");
    exit(1);
  }
  return EXIT_SUCCESS;
}
