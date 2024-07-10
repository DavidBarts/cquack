#ifndef _blackcap_name_error_h_
#define _blackcap_name_error_h_

#include <libgen.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _blackcap_name_error_c_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ void error(const char *, ...);
_extern_ void setmyname(const char *);
_extern_ const char *getmyname(void);

#undef _extern_
#endif
