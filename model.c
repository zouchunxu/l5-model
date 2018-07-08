#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "connect.h"

zend_class_entry *l5model_Model_class;


PHP_METHOD(Model, __construct)
{
    return_value = getThis();
}


PHP_METHOD(Model,connect)
{

    char * host;
    int host_len;

    char * username;
    int username_len;

    char * password;
    int password_len;

    char * database;
    int database_len;

    zend_long port;

//    printf("num=%d\n",ZEND_NUM_ARGS());

    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "ssssl",
    &host,&host_len,
    &username,&username_len,
    &password,&password_len,
    &database,&database_len,
    &port
    )
    ) {

    return ;
    }

//    php_printf("host=%s,host_len=%d\n",host, host_len);
//    php_printf("username=%s,username_len=%d\n",username, username_len);
//    php_printf("password=%s,password_len=%d\n",password, password_len);
//    php_printf("database=%s,database_len=%d\n",database, database_len);
//    php_printf("port=%d\n",port);
    connect_list * clist = add_connect(host,username,password, database,3306);
    return_value = getThis();
}



static const zend_function_entry model_funcs[] = {
        PHP_ME(Model,			connect,        NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Model,			__construct,        NULL, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
        PHP_FE_END
};





void model_init()
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY( ce, "Model", model_funcs );
    l5model_Model_class = zend_register_internal_class(&ce);
}