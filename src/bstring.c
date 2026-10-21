#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../include/bstring.h"
#include "../include/internal/bstring.h"
#include "../include/internal/char.h"
#include "../include/internal/cstring.h"

/* --- Public API Implementation --- */

bstring
bstring_new(cstring cstr)
{
    return bstring_new_with_length(cstr, strlen(cstr));
}

cstring
bstring_to_cstr(bstring bstr)
{
    return bstr.str;
}

usize
bstring_length(bstring bstr)
{
    return bstr.length;
}

bstring
bstring_concat(bstring base, bstring suffix)
{
    return bstring_concat_cstr_with_length(
        base, suffix.str, strlen(suffix.str));
}

bstring
bstring_concat_cstr(bstring base, cstring suffix)
{
    return bstring_concat_cstr_with_length(base, suffix, strlen(suffix));
}

bstring
bstring_copy(bstring bstr)
{
    cstring str = cstring_copy(bstr.str, bstr.length);
    if (str == NULL)
        return BSTRING_NULL;

    return (bstring){ .str = str, .length = bstr.length };
}

void
bstring_free(bstring* bstr)
{
    free(bstr->str);
    bstr->str = NULL;
    bstr->length = 0;
}

bool
bstring_eq(bstring a, bstring b)
{
    return bstring_eq_cstr_with_length(a, b.str, a.length, b.length);
}

bool
bstring_eq_cstr(bstring a, cstring b)
{
    return bstring_eq_cstr_with_length(a, b, a.length, strlen(b));
}

int
bstring_search(bstring bstr, char c)
{
    for (usize i = 0; i < bstr.length; i++)
        if (bstr.str[i] == c)
            return i;
    return -1;
}

int
bstring_search_substr(bstring bstr, cstring substr)
{
    usize substr_len = strlen(substr);

    if (substr_len == 0)
        return 0;

    if (substr_len > bstr.length || bstr.str == NULL)
        return -1;

    usize count = 0;
    for (usize i = 0; i < bstr.length; i++) {
        if (bstr.str[i] == substr[count])
            count++;
        else {
            i -= count;
            count = 0;
        }

        if (count == substr_len)
            return (int)(i - count + 1);
    }

    return -1;
}

char
bstring_char_at(bstring bstr, usize index)
{
    if (index >= bstr.length)
        return 0;

    return bstr.str[index];
}

bstring
bstring_to_upper(bstring bstr)
{
    cstring cstr = cstring_copy(bstr.str, bstr.length);
    if (cstr == NULL)
        return BSTRING_NULL;

    for (usize i = 0; i < bstr.length; i++)
        cstr[i] = toupper((unsigned char)cstr[i]);

    return bstring_from_owned(cstr, bstr.length);
}

bstring
bstring_to_lower(bstring bstr)
{
    cstring cstr = cstring_copy(bstr.str, bstr.length);
    if (cstr == NULL)
        return BSTRING_NULL;

    for (usize i = 0; i < bstr.length; i++)
        cstr[i] = tolower((unsigned char)cstr[i]);

    return bstring_from_owned(cstr, bstr.length);
}

bstring
bstring_substr(bstring bstr, usize start, usize end)
{
    if (start > bstr.length)
        start = bstr.length;
    if (end > bstr.length)
        end = bstr.length;
    if (end < start)
        end = start;

    usize length = end - start;
    cstring str = cstring_copy_with_start(bstr.str, length, start);
    if (str == NULL)
        return BSTRING_NULL;

    return bstring_from_owned(str, length);
}

bool
bstring_begins_with(bstring bstr, cstring prefix)
{
    usize prefix_len = strlen(prefix);
    if (prefix_len > bstr.length)
        return false;
    return memcmp(bstr.str, prefix, prefix_len) == 0;
}

bool
bstring_ends_with(bstring bstr, cstring suffix)
{
    usize suffix_len = strlen(suffix);
    if (suffix_len > bstr.length)
        return false;
    return memcmp(bstr.str + bstr.length - suffix_len, suffix, suffix_len) == 0;
}

bstring
bstring_trim(bstring bstr)
{
    if (bstr.str == NULL)
        return BSTRING_NULL;

    usize start = 0;
    usize end = bstr.length;

    while (start < end && is_whitespace(bstr.str[start]))
        start++;

    while (end > start && is_whitespace(bstr.str[end - 1]))
        end--;

    return bstring_substr(bstr, start, end);
}
