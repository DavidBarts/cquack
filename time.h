#ifndef _blackcap_name_time_h_
#define _blackcap_name_time_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _blackcap_name_time_c_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ time_t from_time(int, int, time_t);

#undef _extern_
#endif
