#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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

  bstring_free(&sentence);
  bstring_free(&upper);
  bstring_free(&lower);
}

/**
 * Compose an HTTP request line and inspect it.
 */
static void
test_request_pipeline(void)
{
  bstring method = bstring_new("GET ");
  bstring path = bstring_new("/index.html");

  bstring line = bstring_concat(method, path);
  bstring request = bstring_concat_cstr(line, " HTTP/1.1");
  bstring upper = bstring_to_upper(request);

  index_start(1, 0);

  debug("request", "s", request.str, 1);
  debug("upper", "s", upper.str, 1);

  tee(assert(bstring_length(request) == 24));
  tee(assert(bstring_search(request, '/') == 4));
  tee(assert(bstring_char_at(request, 4) == '/'));
  tee(assert(bstring_search(request, 'z') == -1));
  tee(assert(bstring_eq_cstr(request, "GET /index.html HTTP/1.1")));
  tee(assert(bstring_eq_cstr(upper, "GET /INDEX.HTML HTTP/1.1")));

  bstring_free(&line);
  bstring_free(&request);
  bstring_free(&upper);
}

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

  bstring_free(&copy);
}

int
main(void)
{
  run_test(test_build_and_transform);
  run_test(test_request_pipeline);
  run_test(test_copy_is_independent);
  return 0;
}
