#include <mysql/mysql.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../main/main.h"
#include "./sqlapi.h"

MYSQL *InitSQL(char *username, char *password, char *host, char *databases) {
  Connmect *con = (Connmect *)malloc(sizeof(Connmect));
  if (NULL == con) {
    die("CON MALLOC");
  }
  MYSQL *mysql = mysql_init(NULL);
  if (NULL == mysql) {
    die("Mysql Init");
  }
  con->username = username;
  con->password = password;
  con->host = host;
  con->databases = databases;
  my_bool a = true;
  mysql_options(mysql, MYSQL_OPT_RECONNECT, &a);

  mysql_real_connect(mysql, con->host, con->username, con->password,
                     con->databases, 0, NULL, 0);

  return mysql;
}

void ExcuteQuery(MYSQL *mysql, char *SqlQuery) {
  int ping = mysql_ping(mysql);
  if (mysql_real_query(mysql, SqlQuery, strlen(SqlQuery))) {
    printf("mysql_real_query failed: %s, sql: %s\n", mysql_error(mysql),
           SqlQuery);
  }
  MYSQL_RES *res = mysql_store_result(mysql);
  if (res == NULL) {
    free(SqlQuery); // 释放内存
  }
  ReturnField(res);
  mysql_free_result(res);
}

MYSQL_FIELD *ReturnField(MYSQL_RES *res) {
  int ResFields = mysql_num_fields(res);
  MYSQL_ROW ResRow = mysql_fetch_row(res);
  MYSQL_FIELD *ResFiled = mysql_fetch_field(res);
  return ResFiled;
}
