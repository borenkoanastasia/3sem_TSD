#include "../inc/vector.h"

int create_vector(vector *vec, int size)
{
    vec->size = size;
    vec->elements = calloc(vec->size, sizeof(int));
    if (!vec->elements)
    {
        return ERROR_CREATE;
    }
    return OK;
}

void free_vector(vector *vec)
{
    free(vec->elements);
}

void output_vector(vector v)
{
    for (int i = 0; i < v.size; i++)
    {
        printf("%2d, ", *(v.elements + i));
    }
    printf("\n");
}
