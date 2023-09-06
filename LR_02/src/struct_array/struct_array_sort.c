#include "../../inc/struct_array.h"
#include "../../inc/menu.h"
#include "../../inc/help_functions.h"

// Сортировка по названию
int struct_array_sort(countries arr[MAX_STRUCT_COUNT], int len)
{
    countries buf = {{0}, 0, {0}, {0}, {0}, {{0}}};
    for (int struct_index = 0; struct_index < len; struct_index++)
    {
        for (int element_index = 1; element_index < len - struct_index; element_index++)
        {
            if (strcmp(arr[element_index].name, arr[element_index - 1].name) < 0)
            {
                buf = arr[element_index];
                arr[element_index] = arr[element_index - 1];
                arr[element_index - 1] = buf;
            }
        }
    }
    return OK;
}
int struct_array_sort_with(countries arr[MAX_STRUCT_COUNT], int len, size_t *size)
{
    *size += sizeof(countries) + sizeof(int) * 2;

    countries buf = {{0}, 0, {0}, {0}, {0}, {{0}}};
    for (int struct_index = 0; struct_index < len; struct_index++)
    {
        for (int element_index = 1; element_index < len - struct_index; element_index++)
        {
            if (strcmp(arr[element_index].name, arr[element_index - 1].name) < 0)
            {
                buf = arr[element_index];
                arr[element_index] = arr[element_index - 1];
                arr[element_index - 1] = buf;
            }
        }
    }
    return OK;
}
// end - какую ячейку затереть
// start - с какой ячейки двигать
void struct_array_swap(countries arr[MAX_STRUCT_COUNT], int start, int end)
{
    countries buf = arr[start];
    arr[start] = arr[end];
    for (int i = end; i > start + 1; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[start + 1] = buf;
}

int struct_array_partition(countries arr[MAX_STRUCT_COUNT], int first_border, int last_border)
{

    int middle = first_border;
    for (int i = first_border; i < last_border + 1; i++)
    {
        if (strcmp(arr[i].name, arr[middle].name) < 0)
        {
            struct_array_swap(arr, middle, i);
            middle++;
        }
    }
    return middle;
}

int struct_array_partition_with(countries arr[MAX_STRUCT_COUNT], int first_border, int last_border,
                           size_t *size)
{
    *size += 2 * sizeof(int);

    int middle = first_border;
    for (int i = first_border; i < last_border + 1; i++)
    {
        if (strcmp(arr[i].name, arr[middle].name) < 0)
        {
            struct_array_swap(arr, middle, i);
            *size += sizeof(countries) + sizeof(int);
            middle++;
        }
    }
    return middle;
}
void struct_array_quick_sort(countries arr[MAX_STRUCT_COUNT], int first_border,
                             int last_border)
{

    if (first_border >= last_border)
        return;
    //printf("first border = %d\n", first_border);
    //output_countries_type(arr[first_border]);
    //printf("last border = %d\n", last_border);
    //output_countries_type(arr[last_border]);
    int middle = struct_array_partition(arr, first_border, last_border);
    struct_array_quick_sort(arr, first_border, middle);
    struct_array_quick_sort(arr, middle + 1, last_border);
}

void struct_array_quick_sort_with(countries arr[MAX_STRUCT_COUNT], int first_border,
                                  int last_border, size_t *size)
{
    *size += sizeof(int);

    if (first_border >= last_border)
        return;
    int middle = struct_array_partition_with(arr, first_border, last_border, size);
    struct_array_quick_sort_with(arr, first_border, middle, size);
    struct_array_quick_sort_with(arr, middle + 1, last_border, size);
}
