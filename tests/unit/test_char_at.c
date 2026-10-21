#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

static void
test_char_at(void)
{
    bstring bstr = bstring_new("Veritas");

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);

    tee(assert(bstring_char_at(bstr, 0) == 'V'));
    tee(assert(bstring_char_at(bstr, 4) == 't'));
    tee(assert(bstring_char_at(bstr, 6) == 's'));

    bstring_free(&bstr);
}

int
main(void)
{
    run_test(test_char_at);
    return 0;
}
