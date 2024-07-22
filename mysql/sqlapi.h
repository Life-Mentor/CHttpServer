typedef struct {
} ROM;

typedef struct {
  char *username;
  char *password;
  char *host;
  char *databases;
} Connmect;

MYSQL *InitSQL(char *username, char *password, char *host, char *databases);
void ExcuteQuery(MYSQL *mysql, char *SqlQuery);
MYSQL_FIELD *ReturnField(MYSQL_RES *res);

