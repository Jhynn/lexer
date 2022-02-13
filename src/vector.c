#include "vector.h"

struct vector *new_vector (const size_t initial_size)
{
    struct vector *vec = calloc(1, sizeof(*vec));
    if (!vec)
        return NULL;
    vec->real_size = (initial_size > 0) ? initial_size : 32;
    vec->size = 0;
    vec->data = calloc(vec->real_size, sizeof(TYPE));
    return vec;
}

void vec_desallocate(struct vector * const vec, void (*func) (TYPE))
{
    size_t i;
    if (func)
        for (i = 0; i < vec->size; i ++)
            func(vec->data[i]);
    free(vec->data);
    free(vec);
}

void insert_at (struct vector * const vec, const size_t index, TYPE value)
{
    if (index >= vec->real_size)
    {
        size_t new_size = vec->real_size;
        while (new_size <= index)
            new_size <<= 1;
        TYPE *data = realloc(vec->data, sizeof(TYPE) * new_size);
        if (data)
        {
            vec->data = data;
            vec->real_size = new_size;
        }
        else
            return;
    }
    else if (index >= 0 && index < vec->size)
    {
        memmove(&vec->data[index + 1], &vec->data[index], sizeof(TYPE) * (vec->size - index));
    }

    vec->data[index] = value;
    vec->size ++;
}

void remove_at (struct vector * const vec, const size_t index)
{
    if (index < 0 || index > vec->size)
        return;
    if (index < vec->size)
        memmove(&vec->data[index], &vec->data[index + 1], (vec->size - index) * sizeof(TYPE));
    vec->size --;
}

struct vector *copy_vector (struct vector * const vec)
{
    struct vector *v = new_vector(vec->size);
    memcpy(v->data, vec->data, sizeof(TYPE) * vec->size);
    v->size = vec->size;
    return v;
}

void push_back (struct vector * const vec, TYPE value)
{
    insert_at(vec, vec->size, value);
}

TYPE* vec_front(struct vector * const vec)
{
    return &vec->data[0];
}

TYPE* vec_back(struct vector * const vec)
{
    return &vec->data[vec->size - 1];
}

TYPE* vec_data(struct vector * const vec)
{
    return vec->data;
}

TYPE pop_back(struct vector * const vec)
{
    TYPE val = *vec_back(vec);
    remove_at(vec, vec->size - 1);
    return val;
}
