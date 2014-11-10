/*
 * cdecl - Parse C declarations into human readable string
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag { IDENTIFIER, TYPE, QUALIFIER };

struct token {
  enum type_tag type;
  char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define pop stack[top--]
#define push(s) stack[++top]=s

enum type_tag classify_string(void) {
  // look at the current token and
  // return a value of TYPE, QUALIFIER, or IDENTIFIER in this.type
}

void gettoken(void) {
  // read next token into this.string
  // if it is alphanumeric, classify string
  // else it must be a single character token
  // this.type = the token itself; terminate this.string with nul
}

void read_to_first_identifier(void) {
  // gettoken and push it onto to the stack until the first identifier is read
  // print "identifer is", this.string
  // gettoken
}

void deal_with_function_args(void) {
  // read past closing ')' print out "function returning"
}

void deal_with_arrays(void) {
  // while you've got "[size]" print it out and read past it
}

void deal_with_any_pointers(void) {
  // while you've got "*" on the stack print "pointer to" and pop it
}

void deal_with_declarator(void) {
  // if this.type is '[' deal_with_arrays
  // if this.type is '(' deal_with_function_args
  // deal_with_any_pointers
  // while there's stuff on the stack
  // if it's a '('
  // pop it and gettoken; it should be the closing ')'
  // deal_with_declarator
  // else pop it and print it
}

int main(void) {
  read_to_first_identifier();
  deal_with_declarator();
  printf("\n");

  return 0;
}
