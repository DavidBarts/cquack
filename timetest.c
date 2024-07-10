#include "time.h"
#include "error.h"

#include <stdlib.h>
#include <stdio.h>

static const char *seetime(time_t *);

int main(int argc, char *argv[]) {
    setmyname("timetest");
    if (argc < 2) {
        error("expecting UNIX timestamp");
        exit(1);
    }
    time_t whenever = strtol(argv[1], NULL, 10);
    printf("Current time is %s", ctime(&whenever));
    time_t alarm = from_time(2, 30, whenever);
    printf("Alarm for 02:30 would ring at %s", seetime(&alarm));
    alarm = from_time(16, 0, whenever);
    printf("Alarm for 16:00 would ring at %s", seetime(&alarm));
    alarm = from_time(23, 45, whenever);
    printf("Alarm for 23:45 would ring at %s", seetime(&alarm));
    return 0;
}

static const char *seetime(time_t *time) {
    if (*time < 0) {
        return "(not representable)\n";
    } else {
        return ctime(time);
    }
}
