/*
 * cdecl - Parse C declarations into human readable string
 */

#include <stdio.h>

#define MAXTOKENLEN 64
#define MAXTOKENS 16

enum type_tag { IDENTIFIER, TYPE, QUALIFIER };

struct token {
  char string[MAXTOKENLEN];
  enum type_tag type;
};

struct token stack[MAXTOKENS];
struct token this;

int main(void) {
  /*find_first_identifier();*/
  /*deal_with_declaration();*/
  printf("%s\n", this.string);

  return 0;
}
