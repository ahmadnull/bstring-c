#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

/**
 * Test bstring_new
 */
static void
test_new(void)
{
    cstring cstr = "Hello World!";
    bstring bstr = bstring_new(cstr);

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 2);
    debug("cstr", "s", cstr, 2);
    debug("bstr length", "zu", bstr.length, 1);
    debug("cstr length", "zu", strlen(cstr), 1);

    tee(assert(bstr.length == strlen(cstr)));
    tee(assert(strcmp(bstr.str, cstr) == 0));

    bstring_free(&bstr);
}

int
main(void)
{
    run_test(test_new);
    return 0;
}
