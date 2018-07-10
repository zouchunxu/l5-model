/* l5_model extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_l5_model.h"
#include "model.h"

/* {{{ void l5_model_test1()
 */
PHP_FUNCTION(l5_model_test1)
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

	printf("num=%d\n",ZEND_NUM_ARGS());

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssss",
											   &host,&host_len,
											   &username,&username_len,
											   &password,&password_len,
                                               &database,&database_len)) {

		return ;
	}
    char  arr[255];
}
/* }}} */

void testVar(char * str){
    php_printf("test_var=%s\n",str);
}


/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(l5_model)
{
#if defined(ZTS) && defined(COMPILE_DL_L5_MODEL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(l5_model)
{

    model_init();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(l5_model)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "l5_model support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_l5_model_test1, 0, 0, 4)
    ZEND_ARG_INFO(0, host)
    ZEND_ARG_INFO(0, username)
    ZEND_ARG_INFO(0, password)
    ZEND_ARG_INFO(0, database)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_l5_model_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ l5_model_functions[]
 */
const zend_function_entry l5_model_functions[] = {
	PHP_FE(l5_model_test1,		arginfo_l5_model_test1)
	PHP_FE_END
};
/* }}} */

static const zend_module_dep php_mysqlnd_deps[] = {
        ZEND_MOD_REQUIRED("mysqlnd")
        ZEND_MOD_END
};

/* {{{ l5_model_module_entry
 */
zend_module_entry l5_model_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	php_mysqlnd_deps,
	"l5_model",					/* Extension name */
	l5_model_functions,			/* zend_function_entry */
	PHP_MINIT(l5_model),							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(l5_model),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(l5_model),			/* PHP_MINFO - Module info */
	PHP_L5_MODEL_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_L5_MODEL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(l5_model)
#endif
