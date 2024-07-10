#ifndef _blackcap_name_main_h_
#define _blackcap_name_main_h_

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _blackcap_name_main_c_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ bool once;

#undef _extern_
#endif
