#ifndef _blackcap_name_must_h_
#define _blackcap_name_must_h_

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _blackcap_name_must_c_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ void *must_malloc(size_t);
_extern_ void *must_realloc(void *, size_t);
_extern_ char *must_strdup(const char *);

#undef _extern_
#endif
