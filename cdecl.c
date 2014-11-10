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
  char *p = this.string;
  // look at the current token and
  // return a value of TYPE, QUALIFIER, or IDENTIFIER in this.type
  if(!strcmp(p, "const")) {
    strcpy(p, "read-only");
    return QUALIFIER;
  }

  if(!strcmp(p, "volatile")) return QUALIFIER;
  if(!strcmp(p, "static"))   return QUALIFIER;
  if(!strcmp(p, "void"))     return TYPE;
  if(!strcmp(p, "char"))     return TYPE;
  if(!strcmp(p, "int"))      return TYPE;
  if(!strcmp(p, "float"))    return TYPE;
  if(!strcmp(p, "short"))    return TYPE;
  if(!strcmp(p, "long"))     return TYPE;
  if(!strcmp(p, "double"))   return TYPE;
  if(!strcmp(p, "signed"))   return TYPE;
  if(!strcmp(p, "unsigned")) return TYPE;
  if(!strcmp(p, "struct"))   return TYPE;
  if(!strcmp(p, "union"))    return TYPE;
  if(!strcmp(p, "enum"))     return TYPE;
  return IDENTIFIER;
}

void gettoken(void) {
  // read next token into this.string
  char *p = this.string;

  while((*p = getc(stdin)) == ' ');

  // if it is alphanumeric, classify string
  if(isalnum(*p)) {
    while(isalnum(*++p = getc(stdin)));
    ungetc(*p, stdin);
    *p = '\0';
    this.type = classify_string();
    return;
  }

  // else it must be a single character token
  // this.type = the token itself; terminate this.string with nul
  if(*p == '*') {
    strcpy(p, "pointer to");
    this.type = '*';
    return;
  }

  this.string[1] = '\0';
  this.type = *p;
}

void read_to_first_identifier(void) {
  // gettoken and push it onto to the stack until the first identifier is read
  gettoken();

  while(this.type != IDENTIFIER) {
    push(this);
    gettoken();
  }
  // print "identifer is", this.string
  printf("%s is ", this.string);

  // gettoken
  gettoken();
}

void deal_with_function_args(void) {
  // read past closing ')' print out "function returning"
  while(this.type != ')')
    gettoken();
  gettoken();
  printf("function returning ");
}

void deal_with_arrays(void) {
  // while you've got "[size]" print it out and read past it
  while(this.type == '[') {
    printf("array ");

    gettoken();
    if(isdigit(this.string[0])) {
      printf("0..%d ", atoi(this.string)-1);
      gettoken();
    }
    gettoken();
    printf("of ");
  }
}

void deal_with_any_pointers(void) {
  // while you've got "*" on the stack print "pointer to" and pop it
  while(stack[top].type == '*')
    printf("%s ", pop.string);
}

void deal_with_declarator(void) {
  // if this.type is '[' deal_with_arrays
  if(this.type == '[') deal_with_arrays();
  // if this.type is '(' deal_with_function_args
  if(this.type == '(') deal_with_function_args();

  // deal_with_any_pointers
  deal_with_any_pointers();

  // while there's stuff on the stack
  while(top >= 0) {
    // if it's a '('
    if(stack[top].type == '(') {
      // pop it and gettoken; it should be the closing ')'
      pop;
      gettoken();
      // deal_with_declarator
      deal_with_declarator();
    } else {
      // else pop it and print it
      printf("%s ", pop.string);
    }
  }
}

int main(void) {
  read_to_first_identifier();
  deal_with_declarator();
  printf("\n");

  return 0;
}
