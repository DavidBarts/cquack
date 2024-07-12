#define _blackcap_name_error_c_

#include "error.h"
#include "must.h"

static char *myname = NULL;
static const char *DELIM = ": ";
static const char *TERM = "\n";

void error(const char *format, ...) {
    static bool unbuf = true;
    va_list ap;

    if (unbuf) {
        setvbuf(stderr, NULL, _IOLBF, BUFSIZ);
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
