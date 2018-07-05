PHP_ARG_ENABLE(l5_model, whether to enable l5_model support,
[  --enable-l5_model          Enable l5_model support], no)

if test "$PHP_L5_MODEL" != "no"; then
  AC_DEFINE(HAVE_L5_MODEL, 1, [ Have l5_model support ])
  PHP_NEW_EXTENSION(l5_model,
  l5_model.c,                           \
  model.c
   $ext_shared)

  PHP_ADD_EXTENSION_DEP(l5_model, mysqlnd)
fi
