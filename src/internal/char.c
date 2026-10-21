#include "../../include/internal/char.h"

bool
is_whitespace(char c)
{
    switch (c) {
        case ' ':
            return true;
        case '\t':
            return true;
        case '\n':
            return true;
        case '\r':
            return true;
        default:
            return false;
    }
}
