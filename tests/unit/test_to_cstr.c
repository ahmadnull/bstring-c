#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

/**
 * Test bstring_to_cstr
 */
static void
test_to_cstr(void)
{
    cstring cstr1 = "Tempus Fugit";
    bstring bstr = bstring_new(cstr1);
    cstring cstr2 = bstring_to_cstr(bstr);

    index_start(1, 0);

    debug("cstr1", "s", cstr1, 1);
    debug("bstr", "s", bstr.str, 1);
    debug("cstr2", "s", cstr2, 1);

    tee(assert(strcmp(cstr1, cstr2) == 0));

    bstring_free(&bstr);
}

int
main(void)
{
    run_test(test_to_cstr);
    return 0;
}
