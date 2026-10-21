#include "../../include/internal/bstring.h"
#include "../../include/internal/cstring.h"
#include <stdlib.h>
#include <string.h>

/* --- Private Internal Code --- */

bstring
bstring_from_owned(cstring cstr, usize length)
{
    return (bstring){ .str = cstr, .length = length };
}

bstring
bstring_new_with_length(cstring cstr, usize length)
{
    cstring str = cstring_copy(cstr, length);
    if (str == NULL)
        return BSTRING_NULL;

    return bstring_from_owned(str, length);
}

bstring
bstring_concat_cstr_with_length(bstring base, cstring suffix, usize length)
{
    usize bstr_len = base.length;
    usize cstr_len = length;
    usize new_len = bstr_len + cstr_len;

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
                            usize a_length,
                            usize b_length)
{
    if (a_length != b_length)
        return false;

    for (usize i = 0; i < a_length; i++)
        if (a.str[i] != b[i])
            return false;

    return true;
}
