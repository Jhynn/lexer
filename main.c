// Compile com make se disponível, caso contrário utilize o comando a seguir:
// gcc -I lib src/*.c main.c -o lexer
// E execute dessa forma: ./lexer <arquivo> 
// ou ./lexer - (para ler da entrada padrão (termine com CTRL-D)).


#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"
#include "vector.h"

void desalloc(char *ptr)
{
    if (ptr)
        free(ptr);
}

void print_vec(struct vector * const vec, char *prompt)
{
    if (vec->size == 0)
        return;

    size_t i;

    printf("%s", prompt);
    for (i = 0; i < vec->size; i ++)
        printf("%s, ", vec->data[i]);

    printf("\b\b  \n\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return !printf("Usage: %s [filename]\n", argv[0]);

    FILE *input;
    if (strlen(argv[1]) == 1 && strcmp(argv[1], "-") == 0)
        input = stdin;
    else
        input = fopen(argv[1], "r");

    if (!input)
        return printf("ERROR: can't open %s for reading.", argv[1]);

    struct vector *reservadas = new_vector(10);
    struct vector *operadores = new_vector(10);
    struct vector *constantes = new_vector(10);
    struct vector *delimitadores   = new_vector(10);
    struct vector *identificadores = new_vector(10);

    char *line  = NULL;
    size_t size = 0;

    while (getline(&line, &size, input) != -1)
    {
        char *ptr = line;
        while (*ptr)
        {
            char *next = next_boundary(ptr);
            if (isoperator(*next))
                push_back(operadores, strndup(next, 1));
            else if (isdelimiter(*next))
                push_back(delimitadores, strndup(next, 1));

            size_t length = next - ptr;

            if (isnumber(ptr, length) || isfloat(ptr, length))
                push_back(constantes, strndup(ptr, length));
            else if (isreserved(ptr, length))
                push_back(reservadas, strndup(ptr, length));
            else if (isidentifier(ptr, length))
                push_back(identificadores, strndup(ptr, length));

            ptr = next + 1;
        }
        
        free(line);
        line = NULL;
        size = 0;
    }

    print_vec(delimitadores, "Delimitadores: ");
    print_vec(constantes, "Constantes: ");
    print_vec(operadores, "Operadores: ");
    print_vec(identificadores, "Identificadores: ");
    print_vec(reservadas, "Reservadas: ");

    vec_desallocate(delimitadores, desalloc);
    vec_desallocate(constantes, desalloc);
    vec_desallocate(operadores, desalloc);
    vec_desallocate(identificadores, desalloc);
    vec_desallocate(reservadas, desalloc);

    return 0;
}
