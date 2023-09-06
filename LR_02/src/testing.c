#include "../inc/testing.h"

void test_key_sort(countries table[MAX_STRUCT_COUNT], int len,  int *time, int *memory)
{
    size_t size = 0;
    key arr[MAX_STRUCT_COUNT];
    clock_t start, stop;

    size = sizeof(arr) + sizeof(int);
    make_key_array_from_struct_array(arr, table, len);
    key_array_sort_with(arr, len, &size);
    *memory = size;

    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        //make_key_array_from_struct_array(arr, table, len);
        key_array_sort(arr, len);
    }
    stop = clock();

    *time = stop - start;
}

void test_key_quick_sort(countries table[MAX_STRUCT_COUNT], int len, int *time, int *memory)
{
    size_t size = 0;
    key arr[MAX_STRUCT_COUNT];
    clock_t start, stop;

    size = sizeof(arr) + sizeof(int);
    make_key_array_from_struct_array(arr, table, len);
    key_array_quick_sort_with(arr, 0, len, &size);
    *memory = size;

    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        //make_key_array_from_struct_array(arr, table, len);
        key_array_quick_sort(arr, 0, len);
    }
    stop = clock();

    *time = stop - start;
}

void test_struct_sort(countries table[MAX_STRUCT_COUNT], int len, int *time, int *memory)
{
    size_t size = 0;
    clock_t start, stop;
    struct_array_sort_with(table, len, &size);

    *memory = size;
    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        struct_array_sort(table, len);
    }
    stop = clock();

    *time = stop - start;
}

void test_struct_quick_sort(countries table[MAX_STRUCT_COUNT], int len, int *time, int *memory)
{
    size_t size = 0;
    clock_t start, stop;

    struct_array_quick_sort_with(table, 0, len, &size);

    *memory = size;
    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        struct_array_quick_sort(table, 0, len);
    }
    stop = clock();

    *time = stop - start;
}
