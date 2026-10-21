#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

/**
 * Test bstring_length
 */
static void
test_length(void)
{
    cstring cstr = "Tempus Fugit";
    bstring bstr = bstring_new(cstr);
    size_t c_len = strlen(cstr);
    size_t b_len = bstring_length(bstr);

    index_start(1, 0);

    debug("cstr", "s", cstr, 2);
    debug("bstr", "s", bstr.str, 2);
    debug("cstr length", "zu", c_len, 1);
    debug("bstr length", "zu", b_len, 1);

    tee(assert(b_len == c_len));

    bstring_free(&bstr);
}

int
main(void)
{
    run_test(test_length);
    return 0;
}
