#include "../../inc/key_array.h"
#include "../../inc/help_functions.h"

int key_array_sort(char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN], int len)
{
    char buf[MAX_STRING_FIELD_LEN] = {0};
    for (int struct_index = 0; struct_index < len; struct_index++)
    {
        for (int element_index = 1; element_index < len - struct_index; element_index++)
        {
            if (strcmp(arr[element_index], arr[element_index - 1]) < 0)
            {
                strcpy(buf, arr[element_index]);
                strcpy(arr[element_index], arr[element_index - 1]);
                strcpy(arr[element_index - 1], buf);
            }
        }
    }
    return OK;
}

// end - какую ячейку затереть
// start - с какой ячейки двигать
void key_array_swap(char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN], int start, int end)
{
    char buf[MAX_STRUCT_COUNT];
    strcpy(buf, arr[start]);
    strcpy(arr[start], arr[end]);
    for (int i = end; i > start + 1; i--)
    {
        strcpy(arr[i], arr[i - 1]);
    }
    strcpy(arr[start + 1], buf);
}

int key_array_partition(char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN], int first_border, int last_border)
{
    int middle = first_border;
    for (int i = first_border; i < last_border + 1; i++)
    {
        if (strcmp(arr[i], arr[middle]) < 0)
        {
            key_array_swap(arr, middle, i);
            middle++;
        }
    }
    return middle;
}

void key_array_quick_sort(char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN], int first_border, int last_border)
{
    if (first_border >= last_border)
        return;
    int middle = key_array_partition(arr, first_border, last_border);
    key_array_quick_sort(arr, first_border, middle);
    key_array_quick_sort(arr, middle + 1, last_border);
}


void make_key_array_from_struct_array(char key_arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN],
                                     countries struct_arr[MAX_STRUCT_COUNT], int len)
{
    for (int i = 0; i < len; i++)
    {
        strcpy(key_arr[i], struct_arr[i].name);
    }
}
