#include "connect.h"
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "database.h"
#include "php.h"
#include <string.h>

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
        tmp->curr->username = username;
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


//    php_printf("%s\n",ZCX_INERT_USER);
    MYSQL_STMT *	stmt ;
    stmt = mysql_stmt_init(mysql);


    mysql_stmt_prepare(stmt, sql, strlen(sql));


//    memset(bind, 0, sizeof(bind));

    if (mysql_stmt_execute(stmt)) {
        char * err = mysql_stmt_error(stmt);
        zend_throw_error(NULL, "zcx_sql:%s",err);
        return 1;
    } else {
        char * err = mysql_stmt_error(stmt);
        return 0;
    }

}

int select_user(zval * ret,MYSQLND * mysql,char * sql,int sql_len)
{
//    char str[80];
//    int str_len = sprintf(str,"select * from user limit %d,%d",0,10);
//    printf("sql:%s\n",str);


    int r = mysql_real_query(mysql, sql, sql_len);
    if(r){
        return r;
    }
//    printf("ret:%d\n",r);

    array_init(ret);

    MYSQL_RES * res = mysql_use_result(mysql);
    MYSQL_FIELD		*fields;

    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    zend_ulong	*field_len;
    field_len = mysql_fetch_lengths(res);
    unsigned int num_fields = mysql_num_fields(res);
    fields = mysql_fetch_fields(res);
    int i =0;
    do{
        zval res_suf;
        array_init(&res_suf);
        for (i=0;i<num_fields;i++) {
            if (row[i]) {
                zval rstr;
                ZVAL_STRINGL(&rstr,row[i],field_len[i]);
                add_assoc_zval(&res_suf,fields[i].name,&rstr);
            } else {
                add_assoc_null(&res_suf,fields[i].name);
            }
        }
        add_next_index_zval(ret,&res_suf);
    }while ( row = mysql_fetch_row(res));

    return 0;
}


/*
 * int select_user(int page)
{
    dbCheck();
    char str[80];

    int pageSize = 20;

    page = ( page -1 ) * pageSize;

    int str_len = sprintf(str,"select * from user limit %d,%d",page,pageSize);
    printf("sql:%s\n",str);

//    printf("ret:%d\n",ret);






    php_printf("<table border=1 align='center' width='800px'>");



    while(row = mysql_fetch_row(res)) {
//        for (int i=0;i<num_fields;i++) {
        php_printf("<tr>");
        php_printf("<td>%s</td>",row[0]);
        php_printf("<td>%s</td>",row[1]);
        php_printf("<td>%s</td>",row[2]);
        php_printf("</tr>");
//        }
    }
    php_printf("</table>");

    return ret;

}
 *
 * */

void * find_connect(char * host,char * username)
{
    connect_list * find = head;
}