#include "../inc/choices.h"

void add_country(countries table[MAX_STRUCT_COUNT], int *len)
{
    countries line;
    int rc = input_country(&line, table, *len);
    if (rc == INPUT_NOT_INDIVIDUAL_NAME)
    {
        printf("В таблице не может быть несколько стран с одинаковым именем\n");
        return;
    }
    if (rc != INPUT_OK)
        return;

    rc = add_struct(table, len, line);
    if (rc == STRUCTWORK_ERROR_MAX_COUNT)
    {
        printf("Превышение максимального кол-ва записей (%d)\n", MAX_STRUCT_COUNT);
        return;
    }
    printf("Страна успешно добавлена!\n");
}

void del_country(countries table[MAX_STRUCT_COUNT], int * len)
{
    char name[MAX_STRING_FIELD_LEN] = { 0 };
    int rc = input_name(name, table, *len);
    if (rc != INPUT_NOT_INDIVIDUAL_NAME)
    {
        printf("Такого имени нет в таблице\n");
        return;
    }
    rc = del_struct(table, len, name);
    if (rc == STRUCTWORK_ERROR_MIN_COUNT)
    {
        printf("Превышение минимального кол-ва записей (%d)\n", MIN_STRUCT_COUNT);
        return;
    }
    printf("Страна успешно удалена!\n");
}


void choice_filter(countries table[MAX_STRUCT_COUNT], int len)
{
    char mainland[MAX_STRING_FIELD_LEN];
    char sport_type[MAX_STRING_FIELD_LEN];
    int rc = 0;

    rc = input_filters_fields(mainland, sport_type);
    if (rc == INPUT_OK)
    {
            output_filter_results(mainland, sport_type, table, len);
    }
}
