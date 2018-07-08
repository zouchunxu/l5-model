#include "connect.h"
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "database.h"
#include "php.h"

connect_list * list;

connect_list * head;

connect_list * tail;




connect_list * add_connect(char * host,char * username,char * password,char * database,int port) {
    connect_list * tmp;
    if(list == NULL){
        list = emalloc(sizeof(connect_list));
        head  = tail = tmp = list;
        tmp->curr = emalloc(sizeof(connect_info));
        tmp->curr->host = host;
        tmp->curr->username = password;
        tmp->curr->database = database;
        tmp->curr->password = password;
        tmp->curr->port = port;
        tmp->curr->mysql = db_init(host,port,username,password,database);
        tmp->next = NULL;
    } else {
        tmp = emalloc(sizeof(connect_list));
        tmp->curr = emalloc(sizeof(connect_info));
        tmp->curr->host = host;
        tmp->curr->username = password;
        tmp->curr->database = database;
        tmp->curr->password = password;
        tmp->curr->port = port;
        tmp->curr->mysql = db_init(host,port,username,password,database);
        tmp->next = NULL;
        tail->next = tmp;
        tail = tmp;
    }
    return tail;
}

int insert_user(MYSQLND * mysql,char * sql)
{

    //TODO

//    php_printf("%s\n",ZCX_INERT_USER);
    MYSQL_STMT *	stmt ;
    stmt = mysql_stmt_init(mysql);


    mysql_stmt_prepare(stmt, sql, strlen(sql));


//    memset(bind, 0, sizeof(bind));

    if (mysql_stmt_execute(stmt)) {
        char * err = mysql_stmt_error(stmt);
        php_printf("true,erro=%s\n",err);
        return 1;
    } else {
        char * err = mysql_stmt_error(stmt);
        php_printf("false,erro=%s\n",err);
        return 0;
    }

}

void * find_connect(char * host,char * username)
{
    connect_list * find = head;
}