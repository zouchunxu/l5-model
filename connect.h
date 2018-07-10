#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include <stdarg.h>
#include "ext/mysqlnd/mysqlnd.h"
#include "ext/mysqlnd/mysqlnd_libmysql_compat.h"

typedef struct  {
    char * host;
    char * username;
    char * password;
    char * database;
    int port;
    MYSQLND * mysql;
} connect_info;

typedef struct _connect_list {
    connect_info * curr;
    struct _connect_list * next;
} connect_list;



void * find_connect(char * host,char * username);

connect_list * add_connect(char * host,char * username,char * password,char * database,int port);

int insert_user(MYSQLND * mysql,char * sql);

int select_user(zval * ret,MYSQLND * mysql,char * sql,int sql_len);