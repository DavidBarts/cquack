#define _blackcap_name_list_c_

#include "list.h"
#include "error.h"

#if !defined(LINUX) && !defined(MACOS)
#error "Unknown OS, must define LINUX or MACOS."
#endif

#if (defined(LINUX) && defined(MACOS))
#error "Ambiguous OS, must define LINUX or MACOS."
#endif

static const size_t uidbuf_size = 16;
static const char *pgrep = "pgrep";

void list_mode(void) {
    char uidbuf[uidbuf_size];

    snprintf(uidbuf, uidbuf_size, "%d", getuid());
#ifdef MACOS
    execlp(pgrep, pgrep, "-l", "-f", "-u", uidbuf, getmyname(), NULL);
#endif
#ifdef LINUX
    execlp(pgrep, pgrep, "-a", "-f", "-u", uidbuf, getmyname(), NULL);
#endif
    error("exec failed: %s", strerror(errno));
    exit(1);
}
