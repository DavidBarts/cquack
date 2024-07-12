#define _blackcap_name_must_c_

#include "must.h"

static void die(const char *);

void *must_malloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL) {
        die("malloc failed!\n");
    }
    return ret;
}

void *must_realloc(void *ptr, size_t size) {
    void *ret = realloc(ptr, size);
    if (ret == NULL) {
        die("realloc failed!\n");
    }
    return ret;
}

char *must_strdup(const char *s) {
    char *ret = strdup(s);
    if (ret == NULL) {
        die("strdup failed!\n");
    }
    return ret;
}

/* write directly to stderr. do not call the normal error printer, do not
   use stdio, do not collect $200. reason: being out of memory, they might
   fail. then, of course, abort. */
static void die(const char *epitaph) {
    write(2, epitaph, strlen(epitaph));
    abort();
}
