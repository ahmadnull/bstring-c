#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../include/bstring.h"

bstring bstring_new_with_length(cstring cstr, size_t length);
bstring bstring_concat_cstr_with_length(bstring base, cstring suffix,
                                        size_t length);
bool bstring_eq_cstr_with_length(bstring a, cstring b, size_t a_length,
                                 size_t b_length);

bstring bstring_new(cstring cstr) {
  return bstring_new_with_length(cstr, strlen(cstr));
}

bstring bstring_new_with_length(cstring cstr, size_t length) {
  return (bstring){.str = cstr, .length = length};
}

cstring bstring_to_cstr(bstring bstr) { return bstr.str; }

bstring bstring_concat(bstring base, bstring suffix) {
  return bstring_concat_cstr_with_length(base, suffix.str, strlen(suffix.str));
}

bstring bstring_concat_cstr(bstring base, cstring suffix) {
  return bstring_concat_cstr_with_length(base, suffix, strlen(suffix));
}

bstring bstring_concat_cstr_with_length(bstring base, cstring suffix,
                                        size_t length) {
  size_t bstr_len = base.length;
  size_t cstr_len = length;
  size_t new_len = bstr_len + cstr_len;

  cstring new_str = malloc(new_len + 1);
  if (new_str == NULL)
    return (bstring){.str = NULL, .length = 0};

  memcpy(new_str, base.str, bstr_len);
  memcpy(new_str + bstr_len, suffix, cstr_len + 1);

  return bstring_new_with_length(new_str, new_len);
}

bstring bstring_copy(bstring bstr) {
  cstring str = malloc(bstr.length + 1);
  memcpy(str, bstr.str, bstr.length + 1);

  return (bstring){.str = str, .length = bstr.length};
}

BSTRING_EXPORT bool bstring_eq(bstring a, bstring b) {
  return bstring_eq_cstr_with_length(a, b.str, a.length, b.length);
}

BSTRING_EXPORT bool bstring_eq_cstr(bstring a, cstring b) {
  return bstring_eq_cstr_with_length(a, b, a.length, strlen(b));
}

bool bstring_eq_cstr_with_length(bstring a, cstring b, size_t a_length,
                                 size_t b_length) {
  if (a_length != b_length)
    return false;

  for (size_t i = 0; i < a_length; i++)
    if (a.str[i] != b[i])
      return false;

  return true;
}
