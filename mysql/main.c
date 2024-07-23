#include <assert.h>
#include <errno.h>
#include <mysql/mysql.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "sqlapi.h"

int main(int argc, char *argv[]) 
{
  MYSQL *con = InitSQL("root", "qpal", "localhost", "duck");
  ExecuteQuery(con, "select * from user");

  return EXIT_SUCCESS;
}
