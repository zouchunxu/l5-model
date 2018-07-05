/* l5_model extension for PHP */

#ifndef PHP_L5_MODEL_H
# define PHP_L5_MODEL_H

extern zend_module_entry l5_model_module_entry;
# define phpext_l5_model_ptr &l5_model_module_entry

# define PHP_L5_MODEL_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_L5_MODEL)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_L5_MODEL_H */
