#ifndef _blackcap_name_quack_h_
#define _blackcap_name_quack_h_

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#ifdef _blackcap_name_quack_c_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ void quack(void);

#undef _extern_
#endif
