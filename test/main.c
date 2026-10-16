#include "../include/bstring.h"
#include <stdio.h>

int main(int argc, char **argv) {
  bstring s1 = bstring_new("Hello World!");
  printf("s1: %s\n", bstring_to_cstr(s1));

  bstring s2 = bstring_concat_cstr(s1, " Hello Banana!");
  printf("s2: %s\n", bstring_to_cstr(s2));

  bstring s3 = bstring_new(" Hello Banana!");
  bstring s4 = bstring_concat(s1, s3);
  printf("s4: %s\n", bstring_to_cstr(s4));

  bstring s5 = bstring_copy(s1);
  printf("s5: %s\n", bstring_to_cstr(s5));

  printf("s1 == s2: %s\n", bstring_eq(s1, s2) ? "true" : "false");
  printf("s4 == s2: %s\n", bstring_eq(s4, s2) ? "true" : "false");
  printf("s5 == s1: %s\n", bstring_eq(s5, s1) ? "true" : "false");
}
