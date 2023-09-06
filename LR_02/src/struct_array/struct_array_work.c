#include "../../inc/struct_array.h"
#include "../../inc/help_functions.h"

int add_struct(countries arr[MAX_STRUCT_COUNT], int *len, countries add_element)
{
    if (*len + 1 > MAX_STRUCT_COUNT)
        return STRUCTWORK_ERROR_MAX_COUNT;
    arr[*len] = add_element;
    *len += 1;
    return STRUCTWORK_OK;
}

int del_struct(countries arr[MAX_STRUCT_COUNT], int *len, char name[MAX_STRING_FIELD_LEN])
{
    int num_del_element = 0;

    if (*len - 1 < MIN_STRUCT_COUNT)
        return STRUCTWORK_ERROR_MIN_COUNT;

    num_del_element = search_struct_by_name(arr, name, *len);

    for (int i = num_del_element; i < *len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    clear_contries(arr + *len);
    *len -= 1;
    return STRUCTWORK_OK;
}
