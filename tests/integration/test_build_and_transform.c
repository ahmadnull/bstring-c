#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

/**
 * Build a string from parts, then transform it end-to-end.
 */
static void
test_build_and_transform(void)
{
  bstring greeting = bstring_new("Hello");
  bstring target = bstring_new(" World");

  bstring sentence = bstring_concat(greeting, target);
  bstring upper = bstring_to_upper(sentence);
  bstring lower = bstring_to_lower(sentence);

  index_start(1, 0);

  debug("sentence", "s", sentence.str, 1);
  debug("upper", "s", upper.str, 1);
  debug("lower", "s", lower.str, 1);

  tee(assert(bstring_length(sentence) == 11));
  tee(assert(bstring_eq_cstr(sentence, "Hello World")));
  tee(assert(bstring_eq_cstr(upper, "HELLO WORLD")));
  tee(assert(bstring_eq_cstr(lower, "hello world")));
  tee(assert(!bstring_eq(sentence, upper)));

  bstring_free(&greeting);
  bstring_free(&target);
  bstring_free(&sentence);
  bstring_free(&upper);
  bstring_free(&lower);
}

int
main(void)
{
  run_test(test_build_and_transform);
  return 0;
}
