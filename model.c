#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "connect.h"

#define PHP_ZCX_MYSQL_RES_NAME "zcx_mysql"
static int academy_zcx_mysql_descriptor;


zend_class_entry *l5model_Model_class;


PHP_METHOD(Model, __construct)
{
    zval tmp;
    array_init(&tmp);
    zend_update_property(l5model_Model_class, getThis(), "wheres", sizeof("wheres")-1, &tmp);
    return_value = getThis();
}


PHP_METHOD(Model,connect)
{

    char * host;
    size_t host_len;

    char * username;
    size_t username_len;

    char * password;
    size_t password_len;

    char * database;
    size_t database_len;

    zend_long port;


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
    connect_list * clist = add_connect(host,username,password, database,port);
    zval tmp;
    ZVAL_RES(&tmp,  zend_register_resource(clist, academy_zcx_mysql_descriptor));
    zend_update_property(l5model_Model_class, getThis(), "connect", sizeof("connect")-1, &tmp);
    return_value = getThis();
}

PHP_METHOD(Model,where)
{
    zval * left = NULL;
    zval * opt = NULL;
    zval * right = NULL;
    zend_long cnt;

    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(),"z|zz",&left,&opt,&right)) {
        return ;
    }

    zval rv;

    zval * z = zend_read_property(l5model_Model_class, getThis(),"wheres", sizeof("wheres")-1, 0, &rv);
    cnt = zend_array_count(Z_ARRVAL_P(z));

    int par_type = Z_TYPE_P(left);

    if (par_type == IS_ARRAY) {
        add_index_zval(z,cnt,left);
    } else if(par_type == IS_STRING)  {
        zval res_suf;
        array_init(&res_suf);
        add_index_zval(&res_suf,0,left);
        if(right == NULL){

            zend_string *str = zend_string_init("=", sizeof("=")-1, 0);
            add_index_str(&res_suf,1,str);
            zval * tmp;
            tmp = opt;
            right = tmp;
        } else {
            add_index_zval(&res_suf,1,opt);
        }

        add_index_zval(&res_suf,2,right);

        add_index_zval(z,cnt,&res_suf);
    } else {
        zend_error(E_ERROR, "参数错误！");
    }

}


PHP_METHOD(Model,get)
{
    zval rv;
    zval * z = zend_read_property(l5model_Model_class, getThis(),"wheres", sizeof("wheres")-1, 0, &rv);

    zend_ulong num_key;
    zend_string *str_key;
    zval *zv,*obj;

    char * buf;

    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(z), num_key, str_key, zv) {
        obj = zend_hash_index_find(Z_ARRVAL_P(zv),0);
        int type = Z_TYPE_P(obj);
        if(type == IS_ARRAY) {
            char tmp_buf[255000];
            zval * l,r;
            l =  zend_hash_index_find(Z_ARRVAL_P(obj),0);
            r =  zend_hash_index_find(Z_ARRVAL_P(obj),1);

            int wcnt = sprintf(tmp_buf,"%s = \"%s\"",Z_STRVAL_P(l),Z_STRVAL_P(r));
            buf = erealloc(buf,wcnt);
            strcat(buf,wcnt);


        } else if(type == IS_STRING) {

        }


    } ZEND_HASH_FOREACH_END();
}



PHP_METHOD(Model,execute)
{

    char * sql;
    size_t sql_len;
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "s",
    &sql,&sql_len)
    ) {
    return ;
    }
    zval rv;

    zval * z = zend_read_property(l5model_Model_class, getThis(),"connect", sizeof("connect")-1, 0, &rv);
    zend_resource *res = Z_RES_P(z);
    connect_list * clist = (connect_list*)res->ptr;

    int s =  insert_user(clist->curr->mysql,sql);
    RETURN_LONG(s);
}

PHP_METHOD(Model,query)
{
    char * sql;
    size_t sql_len;
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "s",
    &sql,&sql_len)
    ) {
    return ;
    }
    zval rv;

    zval * z = zend_read_property(l5model_Model_class, getThis(),"connect", sizeof("connect")-1, 0, &rv);
    zend_resource *res = Z_RES_P(z);
    connect_list * clist = (connect_list*)res->ptr;

    select_user(return_value,clist->curr->mysql,sql,sql_len);

}

static const zend_function_entry model_funcs[] = {
        PHP_ME(Model,			connect,        NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Model,			execute,        NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Model,			query,        NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Model,			__construct,        NULL, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
        PHP_ME(Model,			where,        NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Model,			get,        NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};



//static void zcx_mysql_dtor()
//{
//    connect_list * clist  = (connect_list*)rsrc->ptr;
//    do{
//        efree(clist->curr);
//    }while (clist->next != NULL);
//}

void model_init()
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY( ce, "Model", model_funcs );
    l5model_Model_class = zend_register_internal_class(&ce);
    academy_zcx_mysql_descriptor = zend_register_list_destructors_ex(NULL, NULL, PHP_ZCX_MYSQL_RES_NAME, 0);
//    if (academy_zcx_mysql_descriptor == FAILURE)
//        return FAILURE;
}