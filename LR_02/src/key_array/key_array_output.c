#include "../../inc/key_array.h"
#include "../../inc/struct_array.h"
#include "../../inc/help_functions.h"


void key_array_output_table(key key_arr[MAX_STRUCT_COUNT],
                            countries struct_arr[MAX_STRUCT_COUNT], int len)
{
    output_title();

    for (int i = 0; i < len; i++)
    {
         printf("| %2d ", i + 1);
         output_countries_type(struct_arr[key_arr[i].index]);
         printf("\n");
    }
}
