#pragma once

#if defined(_WIN32)
#define BSTRING_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
#define BSTRING_EXPORT __attribute__((visibility("default")))
#else
#define BSTRING_EXPORT
#endif

#include <stddef.h>
#include <stdbool.h>

typedef size_t usize;
typedef char* cstring;

typedef struct {
    cstring  str;
    usize length;
} bstring;

#define BSTRING_NULL (bstring){ .str = NULL, .length = 0 }

BSTRING_EXPORT bstring bstring_new(cstring cstr);
BSTRING_EXPORT cstring bstring_to_cstr(bstring bstr);
BSTRING_EXPORT usize  bstring_length(bstring bstr);
BSTRING_EXPORT bstring bstring_concat(bstring base, bstring suffix);
BSTRING_EXPORT bstring bstring_concat_cstr(bstring base, cstring suffix);
BSTRING_EXPORT bstring bstring_copy(bstring bstr);
BSTRING_EXPORT void    bstring_free(bstring* bstr);
BSTRING_EXPORT bool    bstring_eq(bstring a, bstring b);
BSTRING_EXPORT bool    bstring_eq_cstr(bstring a, cstring b);
BSTRING_EXPORT int     bstring_search(bstring bstr, char c);
BSTRING_EXPORT int     bstring_search_substr(bstring bstr, cstring substr);
BSTRING_EXPORT char    bstring_char_at(bstring bstr, usize index);
BSTRING_EXPORT bstring bstring_to_upper(bstring bstr);
BSTRING_EXPORT bstring bstring_to_lower(bstring bstr);
BSTRING_EXPORT bstring bstring_substr(bstring bstr, usize start, usize end);
BSTRING_EXPORT bool    bstring_begins_with(bstring bstr, cstring prefix);
BSTRING_EXPORT bool    bstring_ends_with(bstring bstr, cstring suffix);
BSTRING_EXPORT bstring bstring_trim(bstring bstr);
