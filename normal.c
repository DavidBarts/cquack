#define _blackcap_name_normal_c_

#include "normal.h"
#include "error.h"
#include "main.h"
#include "must.h"
#include "quack.h"

static const char *ISO8601 = "%Y-%m-%dT%H:%M:%S%z";
static const size_t ISO8601_LEN = 25;
static const int WAIT_FOR_PARENT = 2;
static const int BOTHER = 10;
static const int FIVEMIN = 5 * 60;
static const int ONEMIN = 60;
static const int MAX_SLEEP = 60;
static const size_t VFORMAT_LEN = 128;

static bool sleep_until(time_t);
static void alert(const char *, ...);
static char *vformat(const char *, va_list);

void normal_mode(time_t when, const char *message) {
    pid_t pid = fork();
    if (pid) {
        /* parent */
        char timebuf[ISO8601_LEN];
        strftime(timebuf, ISO8601_LEN, ISO8601, localtime(&when));
        printf("Alarm set for %s. (pid %d)\n", timebuf, pid);
        exit(0);
    }
    /* child */
    if (!once) {
        sleep(WAIT_FOR_PARENT);
        if (sleep_until(when - FIVEMIN)) {
            alert("%s in 5 minutes.\n", message);
        }
        if (sleep_until(when - ONEMIN)) {
            alert("%s in just one minute!\n", message);
        }
    }
    int times = once ? 1 : BOTHER;
    for (int i = 0; i < times; i++) {
        sleep_until(when);
        alert("%s now!\n", message);
        when += ONEMIN;
    }
    if (!once) {
        alert("That was the last time I'll tell you. Bye.\n");
    }
    _exit(0);
}

/* we sleep in stages because time stands still when the system is in
   power-save mode. */
static bool sleep_until(time_t then) {
    int delta = (int) (then - time(NULL));
    if (delta < 0) {
        return false;
    }
    while (delta > 0) {
        sleep(MAX_SLEEP < delta ? MAX_SLEEP : delta);
        delta = (int) (then - time(NULL));
    }
    return true;
}

static void alert(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char *msg = vformat(format, ap);
    va_end(ap);
    write(1, msg, strlen(msg));
    free(msg);
    quack();
}

static char *vformat(const char *format, va_list ap) {
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
