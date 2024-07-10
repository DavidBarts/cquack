#ifndef _blackcap_name_normal_h_
#define _blackcap_name_normal_h_

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#ifdef _blackcap_name_normal_c_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ void normal_mode(time_t, const char *);

#undef _extern_
#endif
