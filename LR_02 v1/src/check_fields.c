#include "../inc/check_fields.h"
#include "../inc/help_functions.h"

// Каждая функция этого модуля должна начинаться с check_field,
// она должна проверять одно из полей структур в common.h на ограничения
// Возращаемое значение 1 - если полученный параметр подходит под ограничения своего поля,
// иначе возвращаемое значение 0

int check_field_name(char *string, countries table[MAX_STRUCT_COUNT], int len)
{
    //printf("string = %s\n", string);
    if (strlen(string) > MAX_NAME_LEN)
        return CHECK_FIELD_BAD;
    int rc = search_struct_by_name(table, string, len);
    if (rc != -1)
    {
        return BAD_NAME;
    }
    return CHECK_FIELD_GOOD;
}

int check_field_people_amount(long long unsigned int people_amount)
{
    //printf("number = %llu\n", people_amount);
    if (people_amount < 1)
        return CHECK_FIELD_BAD;
    if (people_amount > MAX_PEOPLE_AMOUNT)
        return CHECK_FIELD_BAD;
    return CHECK_FIELD_GOOD;
}

int check_field_capital(char *string)
{
    //printf("string = %s\n", string);
    if (strlen(string) > MAX_CAP_LEN)
        return CHECK_FIELD_BAD;
    return CHECK_FIELD_GOOD;
}

int check_field_mainland(char *string)
{
    char mainlands[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    int len = 0;

    get_variants_value_by_key('m', &len, mainlands);

    for (int i = 0; i < len; i++)
    {
        if (strcmp(mainlands[i], string) == 0)
            return CHECK_FIELD_GOOD;
    }
    return CHECK_FIELD_BAD;
}

int check_field_tourism_type(char *string)
{
    char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    int len = 0;

    get_variants_value_by_key('t', &len, types);

    for (int i = 0; i < len; i++)
    {
        if (strcmp(types[i], string) == 0)
            return CHECK_FIELD_GOOD;
    }
    return CHECK_FIELD_BAD;
}

int check_field_exursion_main_type(char *string)
{
    char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    int len = 0;

    get_variants_value_by_key('e', &len, types);

    for (int i = 0; i < len; i++)
    {
        //printf("types[i] = %s, string = %s\n", types[i], string);
        if (strcmp(types[i], string) == 0)
            return CHECK_FIELD_GOOD;
    }
    return CHECK_FIELD_BAD;
}

int check_field_exursion_monument_count(long int count)
{
    if (count < 1)
        return CHECK_FIELD_BAD;
    if (count > MAX_EXURSION_MONUMENTS_COUNT)
        return CHECK_FIELD_BAD;
    return CHECK_FIELD_GOOD;
}

int check_field_sport_type(char *string)
{
    char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    int len = 0;

    get_variants_value_by_key('p', &len, types);

    for (int i = 0; i < len; i++)
    {
        if (strcmp(types[i], string) == 0)
            return CHECK_FIELD_GOOD;
    }
    return CHECK_FIELD_BAD;
}

int check_field_sport_min_price(long int price)
{
    if (price < 1)
        return CHECK_FIELD_BAD;
    if (price > MAX_SPORT_MIN_PRICE)
        return CHECK_FIELD_BAD;
    return CHECK_FIELD_GOOD;
}

int check_field_beach_season(char *string)
{
    char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    int len = 0;

    get_variants_value_by_key('s', &len, types);

    for (int i = 0; i < len; i++)
    {
        if (strcmp(types[i], string) == 0)
            return CHECK_FIELD_GOOD;
    }
    return CHECK_FIELD_BAD;
}

int check_field_beach_temperature_air(int t)
{
    if (t > MAX_TEMPERATURE)
        return CHECK_FIELD_BAD;
    if (t < MIN_TEMPERATURE)
        return CHECK_FIELD_BAD;
    return CHECK_FIELD_GOOD;
}

int check_field_beach_temperature_water(int t)
{
    if (t > MAX_TEMPERATURE)
        return CHECK_FIELD_BAD;
    if (t < MIN_TEMPERATURE)
        return CHECK_FIELD_BAD;
    return CHECK_FIELD_GOOD;
}

int check_field_beach_time_travel(int t)
{
    if (t < 1)
        return CHECK_FIELD_BAD;
    if (t > MAX_TIME_TRAVEL)
        return CHECK_FIELD_BAD;
    return CHECK_FIELD_GOOD;
}


int check_table_by_name(countries table[MAX_STRUCT_COUNT], int len)
{
    char cur_name[MAX_STRING_FIELD_LEN] = { 0 };
    for (int i = 0; i < len; i++)
    {
        strcpy(cur_name, table[i].name);
        for (int j = 0; j < len; j++)
        {
            if (i == j)
                continue;
            if( strcmp(cur_name, table[j].name))
                return CHECK_FIELD_BAD;
        }
    }
    return CHECK_FIELD_GOOD;
}
