#include "lexer.h"

static const char *reserved_words[] = {
    "int", "char", "void", "static", "inline", "float", "struct", "const",
    "typedef", "union", "long", "unsigned", "signed", "double", "return",
    "sizeof", "include", "for", "if", "while", /* ... */ NULL
};

static const char *delimiters = "()[]{}";

static const char *operators = "+-*/^<>=%!";

int isdelimiter(char b)
{
    return strchr(delimiters, b) != NULL;
}

int isoperator(char b)
{
    return strchr(operators, b) != NULL;
}

int isreserved(const char *str, size_t size)
{
    size_t i = 0;
    while (reserved_words[i])
        if (strlen(reserved_words[i]) == size && strncmp(reserved_words[i], str, size) == 0)
            return 1;
        else
            i ++;
    return 0;
}

int isidentifier(char *str, size_t size)
{
    if (!isalpha(str[0]) && str[0] != '_')
        return 0;

    size_t i;
    for (i = 1; i < size; i ++)
        if (!isalnum(str[i]) || str[0] != '_')
            return 0;

    return 1;
}

int isfloat(char *str, size_t size)
{
    if (size < 1)
        return 0;

    size_t i = 0;

    if (!isdigit(str[0]))
        return 0;

    int x = 0;

    for (i = 1; i < size; i ++)
        if (!isdigit(str[i]))
        {
            if (str[i] == '.' && x == 0)
                x ++;
            else
                return 0;
        }

    return 1;
}

int isnumber(char *str, size_t size)
{
    if (size < 1)
        return 0; 

    size_t i = 0;
    for (i = 0; i < size; i++)
        if (!isdigit(str[i]))
            return 0;

    return 1;
}

int isboundary(char b)
{
    return isspace(b) || isoperator(b) || isdelimiter(b);
}

char *next_boundary(char *ptr)
{
    while (*ptr)
        if (isboundary(*ptr))
            return ptr;
        else
            ptr ++;

    return NULL;
}
