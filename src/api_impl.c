#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../include/bstring.h"
#include "internal.c"

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

size_t
bstring_length(bstring bstr)
{
  return bstr.length;
}

bstring
bstring_concat(bstring base, bstring suffix)
{
  return bstring_concat_cstr_with_length(base, suffix.str, strlen(suffix.str));
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

  memcpy(str, bstr.str, bstr.length + 1);

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
  for (size_t i = 0; i < bstr.length; i++)
    if (bstr.str[i] == c)
      return i;
  return -1;
}

char
bstring_char_at(bstring bstr, size_t index)
{
  if (index > bstr.length)
    return 0;

  return bstr.str[index];
}

bstring
bstring_to_upper(bstring bstr)
{
  cstring cstr = cstring_copy(bstr.str, bstr.length);
  if (cstr == NULL)
    return BSTRING_NULL;

  for (size_t i = 0; i < bstr.length; i++)
    cstr[i] = toupper(cstr[i]);

  return bstring_from_owned(cstr, bstr.length);
}

bstring
bstring_to_lower(bstring bstr)
{
  cstring cstr = cstring_copy(bstr.str, bstr.length);
  if (cstr == NULL)
    return BSTRING_NULL;

  for (size_t i = 0; i < bstr.length; i++)
    cstr[i] = tolower(cstr[i]);

  return bstring_from_owned(cstr, bstr.length);
}
