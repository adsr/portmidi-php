PHP_ARG_WITH(portmidi, for portmidi support,
[  --with-portmidi             Include portmidi support])

if test "$PHP_PORTMIDI" != "no"; then
  dnl
  dnl Find header files
  dnl
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/portmidi.h"  
  if test -r $PHP_PORTMIDI/$SEARCH_FOR; then
    PORTMIDI_DIR=$PHP_PORTMIDI
  else
    AC_MSG_CHECKING([for portmidi files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        PORTMIDI_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  if test -z "$PORTMIDI_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please install portmidi development files])
  fi
  PHP_ADD_INCLUDE($PORTMIDI_DIR/include)

  dnl
  dnl Check library
  dnl
  LIBNAME=portmidi
  LIBSYMBOL=Pm_Initialize
  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PORTMIDI_DIR/$PHP_LIBDIR, PORTMIDI_SHARED_LIBADD)
    AC_DEFINE(HAVE_PORTMIDILIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong portmidi lib version or lib not found])
  ],[
    -L$PORTMIDI_DIR/$PHP_LIBDIR -lm
  ])
  PHP_SUBST(PORTMIDI_SHARED_LIBADD)

  PHP_NEW_EXTENSION(portmidi, portmidi.c, $ext_shared)
fi
