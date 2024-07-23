#include <mysql/mysql.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../main/main.h"
#include "./sqlapi.h"

MYSQL *InitSQL(char *username, char *password, char *host, char *databases) {
  Connmect *con = (Connmect *)malloc(sizeof(Connmect));
  if (NULL == con) {
    fprintf(stderr, "Memory allocation for Connmect failed\n");
    free(con);
    exit(EXIT_FAILURE);
  }
  MYSQL *mysql = mysql_init(NULL);
  if (NULL == mysql) {
    fprintf(stderr, "MySQL initialization failed\n");
    free(con);
    exit(EXIT_FAILURE);
  }

  con->username = username;
  con->password = password;
  con->host = host;
  con->databases = databases;

  my_bool reconnect = true;
  mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);

  if (!mysql_real_connect(mysql, con->host, con->username, con->password,
                          con->databases, 0, NULL, 0)) {
    fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(mysql));
    mysql_close(mysql);
    free(con);
    exit(EXIT_FAILURE);
  }

  free(con); // Free the Connmect structure after the connection is established
  return mysql;
}

void ExecuteQuery(MYSQL *mysql, char *SqlQuery) {
  if (mysql_ping(mysql)) {
    fprintf(stderr, "MySQL ping failed: %s\n", mysql_error(mysql));
    return;
  }

  if (mysql_real_query(mysql, SqlQuery, strlen(SqlQuery))) {
    fprintf(stderr, "MySQL query execution failed: %s, SQL: %s\n",
            mysql_error(mysql), SqlQuery);
    return;
  }

  MYSQL_RES *res = mysql_store_result(mysql);
  if (res == NULL) {
    fprintf(stderr, "MySQL store result failed: %s\n", mysql_error(mysql));
    return;
  }

  ROM *rom = ReturnField(res);
  ParsedResult *parsedResult = ParsedSQLData(rom);
  for (int i = 0; i < parsedResult->NumRows; ++i) {
    for (int j = 0; j < parsedResult->NumFields; ++j) {
      printf("%s = %s\t", parsedResult->columns[j], parsedResult->rows[i][j]);
    }
    printf("\n");
  }
  FreeParsedResult(parsedResult);
  mysql_free_result(res);
}

ROM *ReturnField(MYSQL_RES *res) {
  ROM *rom = (ROM *)malloc(sizeof(ROM));
  if (rom == NULL) {
    fprintf(stderr, "Memory allocation for ROM failed\n");
    return NULL;
  }

  int ResFields = mysql_num_fields(res);
  int ResNumRow = mysql_num_rows(res);
  MYSQL_ROW ResRow;

  rom->ResRow = &ResRow;
  rom->ResNumField = ResFields;
  rom->ResNumRow = ResNumRow;
  rom->Res = res;

  return rom;
}

ParsedResult *ParsedSQLData(ROM *RomData) {
  ParsedResult *Result = (ParsedResult *)malloc(sizeof(ParsedResult));
  if (NULL == Result) {
    die("MallocError");
  }

  for (int i = 0; i < RomData->ResNumRow; i++) {
    MYSQL_FIELD *Field = mysql_fetch_field_direct(RomData->Res, i);
    Result->columns[i] = strdup(Field->name);
  }

  Result->rows = (char ***)malloc(RomData->ResNumField * sizeof(char **));
  if (Result->rows == NULL) {
    fprintf(stderr, "Memory allocation for rows failed\n");
    for (int i = 0; i < RomData->ResNumField; ++i) {
      free(Result->columns[i]);
    }
    free(Result->columns);
    free(Result);
    return NULL;
  }
  MYSQL_ROW row;
  int RowIndex = 0;
  while (NULL == (row = mysql_fetch_row(RomData->Res))) {
    Result->rows[RowIndex] =
        (char **)malloc(RomData->ResNumField * sizeof(char *));

    if (Result->rows[RowIndex] == NULL) {
      fprintf(stderr, "Memory allocation for row %d failed\n", RowIndex);
      for (int i = 0; i < RowIndex; ++i) {
        free(Result->rows[i]);
      }
      for (int i = 0; i < RomData->ResNumField; ++i) {
        free(Result->columns[i]);
      }
      free(Result->columns);
      free(Result->rows);
      free(Result);
      return NULL;
    }
    for (int i = 0; i < RomData->ResNumField; ++i) {
      Result->rows[RowIndex][i] = row[i] ? strdup(row[i]) : NULL;
    }
    RowIndex++;
  }
  Result->NumRows = RomData->ResNumRow;
  Result->NumFields = RomData->ResNumField;

  return Result;
}

void FreeParsedResult(ParsedResult *result) {
  if (result == NULL)
    return;

  for (int i = 0; i < result->NumFields; ++i) {
    free(result->columns[i]);
  }
  free(result->columns);

  for (int i = 0; i < result->NumRows; ++i) {
    for (int j = 0; j < result->NumFields; ++j) {
      free(result->rows[i][j]);
    }
    free(result->rows[i]);
  }
  free(result->rows);
  free(result);
}
void OutputSQLData(ParsedResult *SQLData) {}
