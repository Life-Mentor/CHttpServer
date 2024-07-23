#include <mysql/mysql.h>
typedef struct {
  int ResNumRow;
  MYSQL_ROW *ResRow;
  int ResNumField;
  MYSQL_RES *Res;
} ROM;

typedef struct {
  char *username;
  char *password;
  char *host;
  char *databases;
} Connmect;
typedef struct {
  char **columns;
  char ***rows;
  int NumFields;
  int NumRows;
} ParsedResult;

MYSQL *InitSQL(char *username, char *password, char *host, char *databases);
void ExecuteQuery(MYSQL *mysql, char *SqlQuery);
ROM *ReturnField(MYSQL_RES *res);
ParsedResult *ParsedSQLData(ROM *RomData);
void FreeParsedResult(ParsedResult *result);
void OutputSQLData(ParsedResult *SQLData);
