#ifndef _VECTOR_H
#define _VECTOR_H

#include <string.h>
#include <stdlib.h>

#define TYPE char *
#define MIN_SIZE 32

typedef struct vector
{
    TYPE *data;
    size_t size;
    size_t real_size;
} st_vector;

struct vector *new_vector (const size_t);

void vec_desallocate(struct vector * const, void (*func) (TYPE));

void insert_at (struct vector * const, const size_t, TYPE);

void remove_at (struct vector * const, const size_t);

struct vector *copy_vector (struct vector * const);

void push_back (struct vector * const, TYPE);

TYPE* vec_front(struct vector * const);

TYPE* vec_back(struct vector * const);

TYPE* vec_data(struct vector * const);

TYPE pop_back(struct vector * const);

#endif /* vector.h */
