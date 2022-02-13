#ifndef _LEXER_H
#define _LEXER_H

#include <ctype.h>
#include <stddef.h>
#include <string.h>

int isdelimiter(char b);
int isoperator(char b);
int isreserved(const char *str, size_t size);
int isidentifier(char *str, size_t size);
int isfloat(char *str, size_t size);
int isnumber(char *str, size_t size);
int isboundary(char b);
char *next_boundary(char *ptr);

#endif /* lexer.h */
