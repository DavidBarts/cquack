#define _blackcap_name_parsetime_c_

#include "parsetime.h"
#include "error.h"
#include "must.h"

struct parsetime_ctx {
    char *ucopy;
};

static void _parsetime(struct parsetime_ctx *, struct parsetime_ret *, const char *);

struct parsetime_ret parsetime(const char *unparsed) {
    struct parsetime_ctx ctx;
    struct parsetime_ret ret;
    memset(&ctx, 0, sizeof(ctx));
    _parsetime(&ctx, &ret, unparsed);
    if (ctx.ucopy != NULL) {
        free(ctx.ucopy);
    }
    return ret;
}

static void _parsetime(struct parsetime_ctx *ctx, struct parsetime_ret *ret, const char *unparsed) {
    ret->hh = ret->mm = -1;

    const char *sep = ":";
    char *raw_hh, *raw_mm;

    ctx->ucopy = must_strdup(unparsed);

    if ((raw_hh = strtok(ctx->ucopy, sep)) == NULL) {
        return;
    }
    if ((raw_mm = strtok(NULL, sep)) == NULL) {
        /* single value is treated as minutes */
        raw_mm = raw_hh;
        raw_hh = "0";
    }
    if (strtok(NULL, "") != NULL) {
        /* ensure no trailing garbage */
        return;
    }
    errno = 0;
    char *end;
    ret->hh = (int) strtol(raw_hh, &end, 10);
    if (errno || *end) {
        ret->hh = -1;
    }
    ret->mm = (int) strtol(raw_mm, &end, 10);
    if (errno || *end) {
        ret->mm = -1;
    }
}
