#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

static void
test_eq(void)
{
    cstring cstr1 = "Hello!";
    cstring cstr2 = "Hi!";
    bstring bstr1 = bstring_new(cstr1);
    bstring bstr2 = bstring_new(cstr2);

    index_start(1, 0);

    debug("cstr1", "s", cstr1, 1);
    debug("cstr2", "s", cstr2, 1);
    debug("bstr1", "s", bstr1.str, 1);
    debug("bstr2", "s", bstr2.str, 1);

    log("Test returns true");
    tee(assert(bstring_eq(bstr1, bstr1)));
    tee(assert(bstring_eq_cstr(bstr1, cstr1)));

    log("Test returns false");
    tee(assert(!bstring_eq(bstr1, bstr2)));
    tee(assert(!bstring_eq_cstr(bstr1, cstr2)));

    bstring_free(&bstr1);
    bstring_free(&bstr2);
}

int
main(void)
{
    run_test(test_eq);
    return 0;
}
