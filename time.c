#define _blackcap_name_time_c_

#include "time.h"
#include "error.h"

static int ssm(const struct tm *);
static int ssm2(int, int);
static void set_hms(struct tm *, int, int, int);

/* the roundabout way we get a time tomorrow is necessary because DST
   transitions mean a day is not always 24 hours long */
time_t from_time(int hh, int mm, time_t now) {
    struct tm tm;
    tm = *localtime(&now);
    time_t ret;
    int now_ssm = ssm(&tm);
    if (ssm2(hh, mm) <= now_ssm) {
        /* 25:01 past (23h yesterday, 00h today, or 01h today ==> tomorrow */
        time_t then = now - now_ssm + 3600 * 25 + 60;
        tm = *localtime(&then);
    }
    /* set time and retrieve timestamp */
    set_hms(&tm, hh, mm, 0);
    ret = mktime(&tm);
    /* sanity check the result */
    if (ret > 0) {
        struct tm *tp = localtime(&ret);
        if (tp->tm_hour != hh || tp->tm_min != mm) {
            return (time_t) -1;
        }
    }
    return ret;
}

static int ssm(const struct tm *tm) {
    return tm->tm_sec + (tm->tm_hour*60 + tm->tm_min) * 60;
}

static int ssm2(int hh, int mm) {
    return (hh*60 + mm) * 60;
}

static void set_hms(struct tm *tm, int hh, int mm, int ss) {
    tm->tm_sec = ss;
    tm->tm_min = mm;
    tm->tm_hour = hh;
    tm->tm_isdst = -1;
}
