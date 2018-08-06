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
    return_value = getThis();
}


PHP_METHOD(Model,get)
{
    zval rv;
    zval * z = zend_read_property(l5model_Model_class, getThis(),"wheres", sizeof("wheres")-1, 0, &rv);

    zend_ulong num_key;
    zend_string *str_key;
    zval *zv,*obj;

    char * buf = NULL;
    int first = 0;
    int size = 0;
    uint32_t count = zend_array_count(Z_ARRVAL_P(z));

    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(z), num_key, str_key, zv) {

        obj = zend_hash_get_current_data(Z_ARRVAL_P(zv));
        zend_string * obj_val = zval_get_string(obj);
        zval  obj_key ;
        int type = 0;
        if(obj != NULL) {

            type = Z_TYPE_P(obj);
        }
//        printf("type=%d\n",type);

        zend_hash_get_current_key_zval(Z_ARRVAL_P(zv),&obj_key);
//        printf("obj_key=%d\n",Z_TYPE(obj_key));


        if(Z_TYPE(obj_key) == IS_STRING) {
            char tmp_buf[255000];

            int wcnt = sprintf(tmp_buf,"`%s` = \"%s\"",Z_STRVAL(obj_key),ZSTR_VAL(obj_val));
            size += wcnt;
            buf = erealloc(buf,size);
            if(first == 0){
                strcpy(buf,tmp_buf);
            } else {
                strcat(buf,tmp_buf);
            }
        } else if(type == IS_STRING) {

            char tmp_buf[255000];
            zval * r, * o;
            o =  zend_hash_index_find(Z_ARRVAL_P(zv),1);
            r =  zend_hash_index_find(Z_ARRVAL_P(zv),2);

            int wcnt = sprintf(tmp_buf,"`%s` %s \"%s\"",Z_STRVAL_P(obj),Z_STRVAL_P(o),Z_STRVAL_P(r));
            size += wcnt;
            buf = erealloc(buf,size);
            if(first == 0){
                strcpy(buf,tmp_buf);
            } else {
                strcat(buf,tmp_buf);
            }

        } else {

        }

        first++;
        if(first < count) {
            size += sizeof(" and \0")-1;
            buf = erealloc(buf,size);
            strcat(buf," and \0");

        }

//        printf("%s\n",buf);

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