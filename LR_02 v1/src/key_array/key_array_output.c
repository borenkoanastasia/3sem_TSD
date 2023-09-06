#include "../../inc/key_array.h"
#include "../../inc/struct_array.h"
#include "../../inc/help_functions.h"


void key_array_output_table(char key_arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN],
                            countries struct_arr[MAX_STRUCT_COUNT], int len)
{
    int struct_index = 0;

    output_title();

    for (int i = 0; i < len; i++)
    {
         struct_index = search_struct_by_name(struct_arr, key_arr[i], len);
         output_countries_type(struct_arr[struct_index]);
         printf("\n");
    }
}
