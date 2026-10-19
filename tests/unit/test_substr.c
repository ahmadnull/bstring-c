#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

static void
test_substr(void)
{
#define SUBSTRING "VIDI"
  bstring bstr1 = bstring_new("VENI " SUBSTRING " VICI");
  bstring bstr2 = bstring_substr(bstr1, 5, 9);

  index_start(1, 0);

  debug("SUBSTRING", "s", SUBSTRING, 1);
  debug("bstr1", "s", bstr1.str, 2);
  debug("bstr2", "s", bstr2.str, 2);

  tee(assert(strcmp(bstr2.str, SUBSTRING) == 0));

  bstring_free(&bstr1);
  bstring_free(&bstr2);

#undef SUBSTRING
}

int
main(void)
{
  run_test(test_substr);
  return 0;
}
