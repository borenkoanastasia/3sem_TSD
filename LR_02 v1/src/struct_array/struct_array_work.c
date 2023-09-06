#include "../../inc/struct_array.h"
#include "../../inc/help_functions.h"

int add_struct(countries arr[MAX_STRUCT_COUNT], int *len, countries add_element)
{
    if (*len + 1 < MAX_STRUCT_COUNT)
        return STRUCTWORK_ERROR_MAX_COUNT;
    arr[*len] = add_element;
    return STRUCTWORK_OK;
}

int del_struct(countries arr[MAX_STRUCT_COUNT], int *len, int num_del_element)
{

    if (*len - 1 < MIN_STRUCT_COUNT)
        return STRUCTWORK_ERROR_MIN_COUNT;

    for (int i = num_del_element; i < *len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    clear_contries(arr + *len);
    return STRUCTWORK_OK;
}
