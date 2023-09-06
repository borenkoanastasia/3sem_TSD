#include "../inc/help_functions.h"

void make_hours_from_minutes(int minutes, int *res_minutes, int *hours)
{
    *hours = minutes / 60;
    *res_minutes = minutes - *hours * 60;
}

void make_minutes_from_hours(int *res_minutes, int minutes, int hours)
{
    *res_minutes = minutes + hours * 60;
}

void get_variants_value_by_key(char key, int *len,
                               char res_arr[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN])
{
    if (key == 'm')
    {
        strcpy(res_arr[0], "Africa");
        strcpy(res_arr[1], "North America");
        strcpy(res_arr[2], "South America");
        strcpy(res_arr[3], "Australia");
        strcpy(res_arr[4], "Eurasia");
        strcpy(res_arr[5], "Island");
        strcpy(res_arr[6], "Antarctica");
        *len = 7;
    }
    if (key == 'e')
    {
        strcpy(res_arr[0], "nature");
        strcpy(res_arr[1], "art");
        strcpy(res_arr[2], "history");
        *len = 3;
    }
    if (key == 'p')
    {
        strcpy(res_arr[0], "alpine ski");
        strcpy(res_arr[1], "climbing");
        strcpy(res_arr[2], "surfing");
        *len = 3;
    }
    if (key == 's')
    {
        strcpy(res_arr[0], "winter");
        strcpy(res_arr[1], "spring");
        strcpy(res_arr[2], "summer");
        strcpy(res_arr[3], "autumn");
        *len = 4;
    }
    if (key == 't')
    {
        strcpy(res_arr[0], "excursion");
        strcpy(res_arr[1], "beach");
        strcpy(res_arr[2], "sport");
        *len = 3;
    }
}

void clear_string(char *string, int len)
{
    for (int i = 0; i < len; i++)
    {
        string[i] = 0;
    }
}

int search_struct_by_name(countries struct_arr[MAX_STRUCT_COUNT],
                          char key[MAX_STRING_FIELD_LEN], int len)
{
    for (int i = 0; i < len; i++)
    {
         if (strcmp(struct_arr[i].name, key) == 0)
         {
             return i;
         }
    }
    return -1;
}

void clear_contries(countries *elem)
{
    clear_string(elem->name, MAX_NAME_LEN);
    elem->people_amount = 0;
    clear_string(elem->capital, MAX_CAP_LEN);
    clear_string(elem->tourism_type, MAX_STRING_FIELD_LEN);
    clear_string(elem->description.beach.season, MAX_STRING_FIELD_LEN);
    elem->description.beach.time_travel = 0;
    elem->description.beach.temperature_air = 0;
    elem->description.beach.temperature_water = 0;
}
