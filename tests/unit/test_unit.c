#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

/**
 * Test bstring_new
 */
static void
test_new(void)
{
  cstring cstr = "Hello World!";
  bstring bstr = bstring_new(cstr);

  index_start(1, 0);

  debug("bstr", "s", bstr.str, 2);
  debug("cstr", "s", cstr, 2);
  debug("bstr length", "zu", bstr.length, 1);
  debug("cstr length", "zu", strlen(cstr), 1);

  tee(assert(bstr.length == strlen(cstr)));
  tee(assert(strcmp(bstr.str, cstr) == 0));

  bstring_free(&bstr);
}

/**
 * Test bstring_to_cstr
 */
static void
test_to_cstr(void)
{
  cstring cstr1 = "Tempus Fugit";
  bstring bstr = bstring_new(cstr1);
  cstring cstr2 = bstring_to_cstr(bstr);

  index_start(1, 0);

  debug("cstr1", "s", cstr1, 1);
  debug("bstr", "s", bstr.str, 1);
  debug("cstr2", "s", cstr2, 1);

  tee(assert(strcmp(cstr1, cstr2) == 0));

  bstring_free(&bstr);
}

/**
 * Test bstring_length
 */
static void
test_length(void)
{
  cstring cstr = "Tempus Fugit";
  bstring bstr = bstring_new(cstr);
  size_t c_len = strlen(cstr);
  size_t b_len = bstring_length(bstr);

  index_start(1, 0);

  debug("cstr", "s", cstr, 2);
  debug("bstr", "s", bstr.str, 2);
  debug("cstr length", "zu", c_len, 1);
  debug("bstr length", "zu", b_len, 1);

  tee(assert(b_len == c_len));

  bstring_free(&bstr);
}

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
  run_test(test_new);
  run_test(test_to_cstr);
  run_test(test_length);
  run_test(test_concat);
  run_test(test_copy);
  run_test(test_eq);
  run_test(test_search);
  run_test(test_char_at);
  run_test(test_to_upper);
  run_test(test_to_lower);
  return 0;
}
