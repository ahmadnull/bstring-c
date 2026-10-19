#include "../../include/bstring.h"

bstring bstring_from_owned(cstring cstr, size_t length);
bstring bstring_new_with_length(cstring cstr, size_t length);
bstring bstring_concat_cstr_with_length(bstring base, cstring suffix, size_t length);
bool    bstring_eq_cstr_with_length(bstring a, cstring b, size_t a_length, size_t b_length);
