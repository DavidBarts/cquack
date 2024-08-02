#define _blackcap_name_main_c_

#include "main.h"

#include "error.h"
#include "list.h"
#include "must.h"
#include "normal.h"
#include "parsetime.h"
#include "quack.h"
#include "time.h"

#include <time.h>

static const char *lstrip(const char *, char);
static void compat_mode(const char *);
static void help_mode(void);
static char *get_message(int, char *[], int);

int main(int argc, char *argv[]) {
    /* parse subcommand, act on legacy mode */
    setmyname(argv[0]);
    if (argc < 2) {
        error("expecting subcommand or count");
        exit(2);
    }

    const char *arg1 = argv[1];
    int rest;
    once = false;
    if (strcmp(lstrip(arg1, '-'), "once")) {
        /* 'once' not specified */
        rest = 2;
    } else {
        /* 'once' specified */
        if (argc < 3) {
            error("expecting subcommand");
            exit(2);
        }
        once = true;
        arg1 = argv[2];
        rest = 3;
    }

    if (*arg1 == '\0') {
        error("invalid subcommand");
        exit(1);
    }
    if (strchr("0123456789", arg1[0]) != NULL) {
        if (once) {
            error("'once' not valid in compat mode");
            exit(2);
        }
        compat_mode(arg1);
        exit(0);
    }

    const char *subcommand = lstrip(arg1, '-');
    if (!strcmp(subcommand, "help")) {
        help_mode();
        exit(0);
    }
    if (!strcmp(subcommand, "list")) {
        list_mode();
        exit(0);
    }
    if (strcmp(subcommand, "at") && strcmp(subcommand, "in")) {
        error("%s - invalid subcommand", subcommand);
        exit(1);
    }

    if (rest >= argc) {
        error("expecting time argument");
        exit(2);
    }

    struct parsetime_ret parsed = parsetime(argv[rest]);
    time_t when;
    if (!strcmp(subcommand, "in")) {
        if (parsed.hh < 0) {
            /* single value is treated as minutes */
            parsed.hh = 0;
        }
        if (parsed.mm < 0) {
            error("%s - invalid time", argv[rest]);
            exit(1);
        }
        when = time(NULL) + ((parsed.hh * 60) + parsed.mm) * 60;
    } else if(!strcmp(subcommand, "at")) {
        if (parsed.hh < 0 || parsed.mm < 0 || parsed.hh > 23 || parsed.mm > 59) {
            error("%s - invalid time", argv[rest]);
            exit(1);
        }
        when = from_time(parsed.hh, parsed.mm, time(NULL));
        if (when < 0) {
            error("%02s:%02s - no such time", parsed.hh, parsed.mm);
            exit(1);
        }
    } else {
        error("%s - invalid subcommand", subcommand);
        exit(1);
    }

    const char *reminder = get_message(argc, argv, rest+1);
    normal_mode(when, reminder);
}

static const char *lstrip(const char *str, char junk) {
    while (*str == junk) {
        str++;
    }
    return str;
}

static void compat_mode(const char *rtimes) {
    errno = 0;
    char *end;
    int times = (int) strtol(rtimes, &end, 10);
    if (errno || *end) {
        error("%s - invalid count", rtimes);
        exit(1);
    }
    for (int i = 0; i < times; i++) {
        quack();
    }
}

static void help_mode(void) {
    const char *myname = getmyname();
    printf("Usage: %s {help|list}\n", myname);
    printf("       %s [once] {at|in} time [message...]\n", myname);
    fputs("\nAlarm quack.\n\n"
          "Subcommands:\n"
          "help  Print this help message.\n"
          "list  List all running background alarms.\n"
          "in    Request alarm in specified amount of time (hh:mm).\n"
          "at    Request alarm at specified time in the future (hh:mm, 24 hr clock).\n"
          "once  Modifier, only issue a single alert.\n",
          stdout);
}

static char *get_message(int argc, char *argv[], int start) {
    if (start >= argc) {
        return "Time to leave";
    }
    size_t size = 0;
    for (int i = start; i < argc; i++) {
        size += strlen(argv[i]) + 1;
    }
    /* we don't free it, because we need it as long as we're around */
    char *ret = (char *) must_malloc(size);
    char *end = ret;
    int i = start;
    for (;;) {
        end = stpcpy(end, argv[i]);
        if (++i >= argc) {
            break;
        }
        end = stpcpy(end, " ");
    }
    return ret;
}
