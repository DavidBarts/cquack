#ifndef _blackcap_name_parsetime_h_
#define _blackcap_name_parsetime_h_

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef _blackcap_name_parsetime_c_
#define _extern_
#else
#define _extern_ extern
#endif

struct parsetime_ret {
    int hh, mm;
};

_extern_ struct parsetime_ret parsetime(const char *);

#undef _extern_
#endif
