#define _blackcap_name_error_c_

#include "error.h"
#include "must.h"

static char *myname = NULL;
static const size_t VFORMAT_LEN = 128;
static const char *DELIM = ": ";
static const char *TERM = "\n";

void error(const char *format, ...) {
    static bool unbuf = true;
    va_list ap;

    if (unbuf) {
        setvbuf(stderr, NULL, _IOLBF, 0);
        unbuf = false;
    }
    fputs(myname, stderr);
    fputs(DELIM, stderr);
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fputs(TERM, stderr);
}

void setmyname(const char *arg0) {
    if (myname != NULL) {
        free(myname);
    }
    char *work = must_strdup(arg0);
    myname = must_strdup(basename(work));
    free(work);
}

const char *getmyname(void) {
    return myname;
}

char *vformat(const char *format, va_list ap) {
    char *buf = (char *) must_malloc(VFORMAT_LEN);
    va_list ap2;

    va_copy(ap2, ap);
    int status = vsnprintf(buf, VFORMAT_LEN, format, ap2);
    va_end(ap2);
    if (status < 0) {
        buf[0] = '\0';  /* mangled format, return empty string */
    }

    if (status >= VFORMAT_LEN) {
        size_t bufsize = status + 1;
        buf = (char *) must_realloc(buf, bufsize);
        status = vsnprintf(buf, bufsize, format, ap);
        if (status < 0 || status >= bufsize) {
            buf[0] = '\0';  /* two strikes and yer out */
        }
    }

    return buf;
}
