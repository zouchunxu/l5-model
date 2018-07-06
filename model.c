#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

zend_class_entry *l5model_Model_class;


ZEND_METHOD(Model, __construct)
{
return_value = getThis();
}


ZEND_METHOD(Model,connect)
{
    char * host;
    int host_len;

    char * user_name;
    int user_name_len;

    char * password;
    int password_len;

    char * database;
    int database_len;


    long int port;


    if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS(),"ssssl",
        &host,&host_len,&user_name,&user_name_len,
        &password,&password_len,&database,&database_len,&port)) {

        return ;
    }




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