#include <stdlib.h>
#include <string.h>

#include "../../include/internal/cstring.h"

cstring
cstring_copy_with_start(cstring cstr, usize length, usize start)
{
    cstring copy = malloc(length + 1);
    if (copy == NULL)
        return NULL;
    memcpy(copy, cstr + start, length);
    copy[length] = '\0';
    return copy;
}

cstring
cstring_copy(cstring cstr, usize length)
{
    return cstring_copy_with_start(cstr, length, 0);
}
