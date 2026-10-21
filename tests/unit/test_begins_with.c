#include "../../include/bstring.h"

#include "../testing_util.h"
#include <assert.h>
#include <sys/types.h>

index_start(0, 0);

const bool TEE = true;

static void
test_begins_with(void)
{
    bstring bstr = bstring_new("Hello, World!");

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);

    tee(assert(bstring_begins_with(bstr, "Hello")));
    tee(assert(!bstring_begins_with(bstr, "hello")));
    tee(assert(!bstring_begins_with(bstr, "World!")));
    tee(assert(!bstring_ends_with(bstr, "world!")));
    tee(assert(!bstring_begins_with(bstr, "Hi")));

    bstring_free(&bstr);
}

static void
test_begins_with_whole(void)
{
    bstring bstr = bstring_new("Hello");

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);

    tee(assert(bstring_begins_with(bstr, "Hello")));

    bstring_free(&bstr);
}

static void
test_begins_with_longer(void)
{
    bstring bstr = bstring_new("ab");

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);

    tee(assert(!bstring_begins_with(bstr, "abc")));

    bstring_free(&bstr);
}

static void
test_begins_with_empty_substring(void)
{
    bstring bstr = bstring_new("abc");

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);

    tee(assert(bstring_begins_with(bstr, "")));

    bstring_free(&bstr);
}

static void
test_begins_with_empty_bstring(void)
{
    bstring bstr = bstring_new("");

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);

    tee(assert(bstring_begins_with(bstr, "")));
    tee(assert(!bstring_begins_with(bstr, "abc")));

    bstring_free(&bstr);
}

int
main(void)
{
    run_test(test_begins_with);
    run_test(test_begins_with_whole);
    run_test(test_begins_with_longer);
    run_test(test_begins_with_empty_substring);
    run_test(test_begins_with_empty_bstring);

    return 0;
}
