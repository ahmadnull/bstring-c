#include "../../include/bstring.h"

#include "../testing_util.h"

index_start(0, 0);

const bool TEE = true;

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

    bstring_free(&method);
    bstring_free(&path);
    bstring_free(&line);
    bstring_free(&request);
    bstring_free(&upper);
}

int
main(void)
{
    run_test(test_request_pipeline);
    return 0;
}
