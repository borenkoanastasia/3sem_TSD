#include "../../inc/key_array.h"

int key_array_sort(key arr[MAX_STRUCT_COUNT], int len)
{
    key buf;

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

int key_array_sort_with(key arr[MAX_STRUCT_COUNT], int len,
                        size_t *size)
{
    key buf;
    *size += sizeof(buf) + sizeof(int) * 2;

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
void key_array_swap(key arr[MAX_STRUCT_COUNT], int start, int end)
{
    key buf;

    buf = arr[start];
    arr[start] = arr[end];
    for (int i = end; i > start + 1; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[start + 1] = buf;
}

int key_array_partition(key arr[MAX_STRUCT_COUNT], int first_border,
                        int last_border)
{

    int middle = first_border;
    for (int i = first_border; i < last_border + 1; i++)
    {
        if (strcmp(arr[i].name, arr[middle].name) < 0)
        {
            key_array_swap(arr, middle, i);
            middle++;
        }
    }
    return middle;
}
void key_array_quick_sort(key arr[MAX_STRUCT_COUNT], int first_border,
                          int last_border)
{
    if (first_border >= last_border)
        return;
    //output_key_array(arr, first_border, last_border);

    int middle = key_array_partition(arr, first_border, last_border);
    key_array_quick_sort(arr, first_border, middle);
    key_array_quick_sort(arr, middle + 1, last_border);
}


int key_array_partition_with(key arr[MAX_STRUCT_COUNT], int first_border,
                        int last_border, size_t *size)
{
    *size += sizeof(int) * 2;

    int middle = first_border;
    for (int i = first_border; i < last_border + 1; i++)
    {
        if (strcmp(arr[i].name, arr[middle].name) < 0)
        {
            key_array_swap(arr, middle, i);
            middle++;
            *size += sizeof(char) * MAX_STRING_FIELD_LEN;
        }
    }
    return middle;
}

void output_key_array(char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN], int f_b, int l_b)
{
    printf("f_b = %d, l_b = %d\n", f_b, l_b);
    printf("arr[f_b] = %s, arr[l_b] = %s\n", arr[f_b], arr[l_b]);
    /*for (int i = f_b; i < l_b + 1; i++)
    {
        printf("%s ", arr[i]);
    }*/
    printf("\n");
}

void key_array_quick_sort_with(key arr[MAX_STRUCT_COUNT], int first_border,
                          int last_border, size_t *size)
{
    *size += sizeof(int);
    if (first_border >= last_border)
        return;
    //output_key_array(arr, first_border, last_border);

    int middle = key_array_partition_with(arr, first_border, last_border, size);
    key_array_quick_sort_with(arr, first_border, middle, size);
    key_array_quick_sort_with(arr, middle + 1, last_border, size);
}


void make_key_array_from_struct_array(key key_arr[MAX_STRUCT_COUNT],
                                     countries struct_arr[MAX_STRUCT_COUNT], int len)
{
    for (int i = 0; i < len; i++)
    {
        strcpy(key_arr[i].name, struct_arr[i].name);
        key_arr[i].index = i;
    }
}
