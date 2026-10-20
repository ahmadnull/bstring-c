#include "../../include/internal/bstring.h"
#include "../../include/internal/cstring.h"
#include <stdlib.h>
#include <string.h>

/* --- Private Internal Code --- */

bstring
bstring_from_owned(cstring cstr, size_t length)
{
    return (bstring){ .str = cstr, .length = length };
}

bstring
bstring_new_with_length(cstring cstr, size_t length)
{
    cstring str = cstring_copy(cstr, length);
    if (cstr == NULL)
        return BSTRING_NULL;

    return bstring_from_owned(str, length);
}

bstring
bstring_concat_cstr_with_length(bstring base, cstring suffix, size_t length)
{
    size_t bstr_len = base.length;
    size_t cstr_len = length;
    size_t new_len = bstr_len + cstr_len;

    cstring new_str = malloc(new_len + 1);
    if (new_str == NULL)
        return BSTRING_NULL;

    memcpy(new_str, base.str, bstr_len);
    memcpy(new_str + bstr_len, suffix, cstr_len + 1);

    return bstring_from_owned(new_str, new_len);
}

bool
bstring_eq_cstr_with_length(bstring a,
                            cstring b,
                            size_t a_length,
                            size_t b_length)
{
    if (a_length != b_length)
        return false;

    for (size_t i = 0; i < a_length; i++)
        if (a.str[i] != b[i])
            return false;

    return true;
}
