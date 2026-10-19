#include <stdlib.h>
#include <string.h>

#include "../include/bstring.h"

/* --- Private Internal Code --- */

static cstring
cstring_copy(cstring cstr, size_t length)
{
  cstring copy = malloc(length + 1);
  if (copy == NULL)
    return NULL;
  memcpy(copy, cstr, length);
  copy[length] = '\0';
  return copy;
}

static bstring
bstring_from_owned(cstring cstr, size_t length)
{
  return (bstring){ .str = cstr, .length = length };
}

static bstring
bstring_new_with_length(cstring cstr, size_t length)
{
  cstring str = cstring_copy(cstr, length);
  if (str == NULL)
    return (bstring){ .str = NULL, .length = 0 };

  return bstring_from_owned(str, length);
}

static bstring
bstring_concat_cstr_with_length(bstring base, cstring suffix, size_t length)
{
  size_t bstr_len = base.length;
  size_t cstr_len = length;
  size_t new_len = bstr_len + cstr_len;

  cstring new_str = malloc(new_len + 1);
  if (new_str == NULL)
    return (bstring){ .str = NULL, .length = 0 };

  memcpy(new_str, base.str, bstr_len);
  memcpy(new_str + bstr_len, suffix, cstr_len + 1);

  return bstring_from_owned(new_str, new_len);
}

static bool
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
