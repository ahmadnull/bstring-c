#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

/**
 * Test test_copy
 */
static void
test_copy(void)
{
    cstring cstr1 = "Sky is Blue.";
    cstring cstr2 = "Sky is Glue.";
    bstring bstr1 = bstring_new(cstr1);
    bstring bstr2 = bstring_copy(bstr1);
    bstr2.str[7] = 'G';

    index_start(1, 0);

    debug("cstr1", "s", cstr1, 1);
    debug("cstr2", "s", cstr2, 1);
    debug("bstr1", "s", bstr1.str, 1);
    debug("bstr2", "s", bstr2.str, 1);

    tee(assert(strcmp(bstr1.str, cstr1) == 0));
    tee(assert(strcmp(bstr2.str, cstr2) == 0));

    bstring_free(&bstr1);
    bstring_free(&bstr2);
}

int
main(void)
{
    run_test(test_copy);
    return 0;
}
