#define _blackcap_name_quack_c_

#include "quack.h"
#include "must.h"
#include "error.h"

#if !defined(LINUX) && !defined(MACOS)
#error "Unknown OS, must define LINUX or MACOS."
#endif

#if (defined(LINUX) && defined(MACOS))
#error "Ambiguous OS, must define LINUX or MACOS."
#endif

#ifdef MACOS
const char *play_command = "afplay";
const char *quack_sound_file = "misc/quack.mp3";
#endif
#ifdef LINUX
const char *play_command = "paplay";
const char *quack_sound_file = "misc/quack.ogg";
#endif
const bool in_home = true;

static void rstrip(char *, char);

void quack(void) {
    pid_t child = fork();

    if (child != 0) {
        /* parent */
        int status;
        waitpid(child, &status, 0);
        if (WIFEXITED(status)) {
            int estat = WEXITSTATUS(status);
            if (estat) {
                error("%s returned exit status %d", play_command, estat);
            }
        } else if (WIFSIGNALED(status)) {
            error("%s terminated by signal %d", play_command, WTERMSIG(status));
        }

    } else {
        /* child */
        /* we malloc but don't free here, because exec will clean up for us */
        char *qpath;
        if (in_home) {
            char *home;
            if ((home = getenv("HOME")) == NULL) {
                home = "";
            } else {
                home = must_strdup(home);
                rstrip(home, '/');
            }
            size_t size = strlen(home) + 1 + strlen(quack_sound_file) + 1;
            qpath = (char *) must_malloc(size);
            char *end = stpcpy(qpath, home);
            end = stpcpy(end, "/");
            end = stpcpy(end, quack_sound_file);
        } else {
            qpath = (char *) quack_sound_file;
        }
        execlp(play_command, play_command, qpath, NULL);
        error("exec failed: %s", strerror(errno));
        _exit(1);
    }
}

static void rstrip(char *str, char ch)
{
    char *sp = str + strlen(str) - 1;
    while (sp >= str && *sp == ch) {
        *sp-- = '\0';
    }
}
