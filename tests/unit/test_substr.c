#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

static void
test_substr(void)
{
#define SUBSTRING "VIDI"
    bstring bstr1 = bstring_new("VENI " SUBSTRING " VICI");
    bstring bstr2 = bstring_substr(bstr1, 5, 9);
    bstring empty1 = bstring_substr(bstr1, 9, 5);
    bstring empty2 = bstring_substr(bstr1, 14, 20);
    bstring clamped = bstring_substr(bstr1, 5, 100);

    index_start(1, 0);

    debug("SUBSTRING", "s", SUBSTRING, 1);
    debug("bstr1", "s", bstr1.str, 2);
    debug("bstr2", "s", bstr2.str, 2);

    tee(assert(strcmp(bstr2.str, SUBSTRING) == 0));
    tee(assert(bstring_length(empty1) == 0 && strcmp(empty1.str, "") == 0));
    tee(assert(bstring_length(empty2) == 0 && strcmp(empty2.str, "") == 0));
    tee(assert(strcmp(clamped.str, "VIDI VICI") == 0));

    bstring_free(&bstr1);
    bstring_free(&bstr2);
    bstring_free(&empty1);
    bstring_free(&empty2);
    bstring_free(&clamped);

#undef SUBSTRING
}

int
main(void)
{
    run_test(test_substr);
    return 0;
}
