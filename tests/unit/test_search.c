#include "../../include/bstring.h"

#include "../testing_util.h"
#include <assert.h>

index_start(0, 0);

const bool TEE = true;

static void
test_search(void)
{
    bstring bstr = bstring_new("Veritas");

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);

    tee(assert(bstring_search(bstr, 'V') == 0));
    tee(assert(bstring_search(bstr, 't') == 4));
    tee(assert(bstring_search(bstr, 's') == 6));

    bstring_free(&bstr);
}

static void
test_search_substr(void)
{
    bstring bstr = bstring_new("Veritas Vincit");
    cstring cstr1 = "Veritas";
    cstring cstr2 = "Vincit";
    cstring cstr3 = "Falsitas";

    int result1 = bstring_search_substr(bstr, cstr1);
    int result2 = bstring_search_substr(bstr, cstr2);
    int result3 = bstring_search_substr(bstr, cstr3);

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);
    debug("cstr1", "s", cstr1, 1);
    debug("cstr2", "s", cstr2, 1);
    debug("cstr3", "s", cstr3, 1);
    debug("result1", "d", result1, 1);
    debug("result2", "d", result2, 1);
    debug("result3", "d", result3, 1);

    tee(assert(result1 == 0));
    tee(assert(result2 == 8));
    tee(assert(result3 == -1));

    bstring_free(&bstr);
}

static void
test_search_substr_backtracks()
{
    bstring bstr = bstring_new("aaab");
    cstring substr = "aab";

    int result = bstring_search_substr(bstr, substr);

    index_start(1, 0);

    debug("bstr", "s", bstr.str, 1);
    debug("substr", "s", substr, 1);
    debug("result", "d", result, 1);

    tee(assert(result == 1));

    bstring_free(&bstr);
}

int
main(void)
{
    run_test(test_search);
    run_test(test_search_substr);
    run_test(test_search_substr_backtracks);
    return 0;
}
