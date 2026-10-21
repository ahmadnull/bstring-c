#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

static void
test_to_upper(void)
{
    cstring cstr = "Veritas Vincit";
    bstring bstr = bstring_new(cstr);
    bstring bstr_upper = bstring_to_upper(bstr);

    index_start(1, 0);

    debug("cstr", "s", cstr, 2);
    debug("bstr", "s", bstr.str, 2);
    debug("bstr uppercase", "s", bstr_upper.str, 1);

    log("Test that bstring_to_upper doesn't change the original bstring");
    tee(assert(strcmp(bstr.str, cstr) == 0));

    log("Test that bstring_to_upper works correctly");
    tee(assert(strcmp(bstr_upper.str, "VERITAS VINCIT") == 0));

    bstring_free(&bstr);
    bstring_free(&bstr_upper);
}

static void
test_to_lower(void)
{
    cstring cstr = "Veritas Vincit";
    bstring bstr = bstring_new(cstr);
    bstring bstr_lower = bstring_to_lower(bstr);

    index_start(1, 0);

    debug("cstr", "s", cstr, 2);
    debug("bstr", "s", bstr.str, 2);
    debug("bstr lowercase", "s", bstr_lower.str, 1);

    log("Test that bstring_to_lower doesn't change the original bstring");
    tee(assert(strcmp(bstr.str, cstr) == 0));

    log("Test that bstring_to_lower works correctly");
    tee(assert(strcmp(bstr_lower.str, "veritas vincit") == 0));

    bstring_free(&bstr);
    bstring_free(&bstr_lower);
}

int
main(void)
{
    run_test(test_to_upper);
    run_test(test_to_lower);
    return 0;
}
