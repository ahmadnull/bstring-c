#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

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

int
main(void)
{
  run_test(test_search);
  return 0;
}
