#include "../../include/bstring.h"

bstring bstring_from_owned(cstring cstr, usize length);
bstring bstring_new_with_length(cstring cstr, usize length);
bstring bstring_concat_cstr_with_length(bstring base, cstring suffix, usize length);
bool    bstring_eq_cstr_with_length(bstring a, cstring b, usize a_length, usize b_length);
