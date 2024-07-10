#ifndef _blackcap_name_list_h_
#define _blackcap_name_list_h_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _blackcap_name_list_c_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ void list_mode(void);

#undef _extern_
#endif
