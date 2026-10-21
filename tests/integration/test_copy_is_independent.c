#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

/**
 * A copy must be independent from its origin.
 */
static void
test_copy_is_independent(void)
{
    bstring origin = bstring_new("foo bar baz");
    bstring copy = bstring_copy(origin);

    size_t space = bstring_search(copy, ' ');
    copy.str[space] = '_';

    index_start(1, 0);

    debug("origin", "s", origin.str, 1);
    debug("copy", "s", copy.str, 1);

    tee(assert(bstring_eq_cstr(origin, "foo bar baz")));
    tee(assert(bstring_eq_cstr(copy, "foo_bar baz")));

    bstring_free(&origin);
    bstring_free(&copy);
}

int
main(void)
{
    run_test(test_copy_is_independent);
    return 0;
}
