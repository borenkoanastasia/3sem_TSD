#include "../inc/filter.h"

void filter_mainland_sport_type(char mainland[MAX_STRING_FIELD_LEN],
                               char sport_type[MAX_STRING_FIELD_LEN],
                               countries table[MAX_STRUCT_COUNT], int len,
                               countries new_table[MAX_STRUCT_COUNT], int *new_len)
{
    countries cur_table[MAX_STRUCT_COUNT];
    int cur_len = 0;

    for (int i = 0; i < len; i++)
    {
        if (strcmp(table[i].mainland, mainland) == 0 &&
                strcmp(table[i].tourism_type, "sport") == 0)
        {
            cur_table[cur_len++] = table[i];
        }
    }

    for (int i = 0; i < cur_len; i++)
    {
        if (strcmp(cur_table[i].description.sport.type_sport, sport_type) == 0)
        {
            new_table[(*new_len)++] = cur_table[i];
        }
    }
}

void output_filter_results(char mainland[MAX_STRING_FIELD_LEN],
                           char sport_type[MAX_STRING_FIELD_LEN],
                           countries table[MAX_STRUCT_COUNT], int len)
{
    countries new_table[MAX_STRUCT_COUNT];
    int new_len = 0;

    filter_mainland_sport_type(mainland, sport_type, table, len, new_table, &new_len);

    if (new_len > 0)
    {
        output_table(new_table, new_len);
    }
    else
    {
        printf("Нечего показывать\n");
    }
}
