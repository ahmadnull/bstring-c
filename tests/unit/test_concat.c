#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

/**
 * Test bstring_concat & bstring_concat_cstr
 */
static void
test_concat(void)
{
#define BASE "John "
#define SUFFIX "Harvard"

    bstring s1 = bstring_new(BASE);
    bstring s2 = bstring_concat_cstr(s1, SUFFIX);
    bstring s3 = bstring_new(SUFFIX);
    bstring s4 = bstring_concat(s1, s3);

    index_start(1, 0);

    debug("BASE", "s", BASE, 2);
    debug("SUFFIX", "s", SUFFIX, 2);
    debug("BASE + SUFFIX", "s", BASE SUFFIX, 1);
    debug("s1", "s", s1.str, 2);
    debug("s2", "s", s2.str, 2);
    debug("s3", "s", s3.str, 2);
    debug("s4", "s", s4.str, 2);

    tee(assert(strcmp(s2.str, BASE SUFFIX) == 0));
    tee(assert(strcmp(s4.str, BASE SUFFIX) == 0));

    bstring_free(&s1);
    bstring_free(&s2);
    bstring_free(&s3);
    bstring_free(&s4);

#undef BASE
#undef SUFFIX
}

int
main(void)
{
    run_test(test_concat);
    return 0;
}
