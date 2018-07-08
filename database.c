#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include <stdarg.h>
#include "ext/mysqlnd/mysqlnd.h"
#include "ext/mysqlnd/mysqlnd_libmysql_compat.h"
#include <string.h>

MYSQLND * db_init(char * hostname,int port,char * username,char * password,char * database)
{
    MYSQLND * zcx_mysql = NULL;
    zend_bool persistent = TRUE;
    zcx_mysql = mysqlnd_init(1, persistent);

    unsigned int pwd_len = strlen(password);
    unsigned int db_len = strlen(database);
    unsigned int flags = 0;
    char * socket = NULL;

    /* set some required options */
    flags |= CLIENT_MULTI_RESULTS; /* needed for mysql_multi_query() */
    /* remove some insecure options */
    flags &= ~CLIENT_MULTI_STATEMENTS;   /* don't allow multi_queries via connect parameter */



//


    mysqlnd_connect(zcx_mysql, hostname, username, password, pwd_len, database, db_len, port, socket, flags, 1);
    return zcx_mysql;
}