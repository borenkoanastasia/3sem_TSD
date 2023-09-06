#include "../inc/input_data.h"

int input_field_char(char string[MAX_STRING_FIELD_LEN])
{
    char symbol = fgetc(stdin);
    int i = 0;
    while (symbol != '\n')
    {
        //printf("i = %d, MAX_STRING_FIELD = %d\n", i, MAX_STRING_FIELD_LEN);
        if (MAX_STRING_FIELD_LEN <= i)
        {
            return INPUT_ERROR_MAX_STRING_LEN;
        }
        string[i] = symbol;
        i++;
        symbol = fgetc(stdin);
    }
    string[i] = 0;
    return INPUT_OK;
}

int input_name(char name[MAX_STRING_FIELD_LEN], countries table[MAX_STRUCT_COUNT], int len)
{
    printf("Введите название страны:\n");
    int rc = input_field_char(name);
    if (rc == INPUT_ERROR_MAX_STRING_LEN)
    {
        printf("Слишком длинное название, максимально допустимая длина имени: %d\n",
               MAX_STRING_FIELD_LEN - 1);
        return INPUT_ERROR;
    }
    rc = check_field_name(name, table, len);
    if (rc == CHECK_FIELD_BAD_NAME)
    {
        return INPUT_NOT_INDIVIDUAL_NAME;
    }
    if (rc == CHECK_FIELD_BAD)
    {
        printf("Имя не должно быть пустым\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}

int input_people_amount(long long unsigned int *people_amount)
{
    printf("Введите население страны, не больше населения всей земли %ld, не меньше 1\n",
           MAX_PEOPLE_AMOUNT);
    int rc = scanf("%llu", people_amount);
    fgetc(stdin);

    if (rc != 1)
    {
        printf("Ввод некорректен, это должны быть числа указанного диапазона\n");
        return INPUT_ERROR;
    }
    rc = check_field_people_amount(*people_amount);

    if (rc != CHECK_FIELD_GOOD)
    {
        printf("Ввод некорректен, это должны быть числа указанного диапазона\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}


int input_capital(char capital[MAX_STRING_FIELD_LEN])
{
    printf("Введите столицу страны\n");
    int rc = input_field_char(capital);
    if (rc == INPUT_ERROR_MAX_STRING_LEN)
    {
        printf("Слишком длинное название, максимально допустимая длина имени: %d\n",
               MAX_STRING_FIELD_LEN - 1);
        return INPUT_ERROR;
    }
    rc = check_field_capital(capital);
    if (rc == CHECK_FIELD_BAD)
    {
        printf("Имя не должно быть пустым\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}

int input_mainland(char mainland[MAX_STRING_FIELD_LEN])
{
    int len = 0, answer = 0, rc = 0;
    char variants[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    get_variants_value_by_key('m', &len, variants);

    printf("Введите номер материка в списке:\n");

    for (int i = 0; i < len; i++)
    {
        printf("%d. %s\n", i + 1, variants[i]);
    }
    rc = scanf("%d", &answer);
    fgetc(stdin);
    if (rc != 1 || answer > len || answer < 1)
    {
        printf("Некорректный ввод\n");
        return INPUT_ERROR;
    }
    strcpy(mainland, variants[answer - 1]);
    return INPUT_OK;
}

int input_tourism_type(char tourism_type[MAX_STRING_FIELD_LEN])
{
    int len = 0, answer = 0, rc = 0;
    char variants[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    get_variants_value_by_key('t', &len, variants);

    printf("Введите номер типа туризма в списке:\n");

    for (int i = 0; i < len; i++)
    {
        printf("%d. %s\n", i + 1, variants[i]);
    }
    rc = scanf("%d", &answer);
    fgetc(stdin);
    if (rc != 1 || answer > len || answer < 1)
    {
        printf("Некорректный ввод\n");
        return INPUT_ERROR;
    }
    strcpy(tourism_type, variants[answer - 1]);
    return INPUT_OK;
}

int input_excursion_main_type(char main_type[MAX_STRING_FIELD_LEN])
{
    int len = 0, answer = 0, rc = 0;
    char variants[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    get_variants_value_by_key('e', &len, variants);

    printf("Введите номер типа экскурсий в списке:\n");

    for (int i = 0; i < len; i++)
    {
        printf("%d. %s\n", i + 1, variants[i]);
    }
    rc = scanf("%d", &answer);
    if (rc != 1 || answer > len || answer < 1)
    {
        printf("Некорректный ввод\n");
        return INPUT_ERROR;
    }
    strcpy(main_type, variants[answer - 1]);
    return INPUT_OK;
}

int input_excursion_monuments_count(long int *monuments_count)
{
    printf("Введите количество памятников, не больше %ld, не меньше 1\n",
           MAX_PEOPLE_AMOUNT);
    int rc = scanf("%ld", monuments_count);
    fgetc(stdin);
    if (rc != 1)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }
    rc = check_field_people_amount(*monuments_count);

    if (rc != CHECK_FIELD_GOOD)
    {
        printf("Ввод некорректен\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}

int input_beach_season(char season[MAX_STRING_FIELD_LEN])
{
    int len = 0, answer = 0, rc = 0;
    char variants[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    get_variants_value_by_key('s', &len, variants);

    printf("Введите номер сезона в списке:\n");

    for (int i = 0; i < len; i++)
    {
        printf("%d. %s\n", i + 1, variants[i]);
    }
    rc = scanf("%d", &answer);
    fgetc(stdin);
    if (rc != 1 || answer > len || answer < 1)
    {
        printf("Некорректный ввод\n");
        return INPUT_ERROR;
    }
    strcpy(season, variants[answer - 1]);
    return INPUT_OK;
}

int input_beach_temperature_air(int *temperature_air)
{
    printf("Введите температуру воздуха, не больше %d, не меньше %d\n",
           MAX_TEMPERATURE, MIN_TEMPERATURE);
    int rc = scanf("%d", temperature_air);
    fgetc(stdin);
    if (rc != 1)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }
    rc = check_field_beach_temperature_air(*temperature_air);
    if (rc == CHECK_FIELD_BAD)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}

int input_beach_temperature_water(int *temperature_water)
{
    printf("Введите температуру воды, не больше %d, не меньше %d\n",
           MAX_TEMPERATURE, MIN_TEMPERATURE);
    int rc = scanf("%d", temperature_water);
    fgetc(stdin);
    if (rc != 1)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }

    rc = check_field_beach_temperature_water(*temperature_water);
    if (rc == CHECK_FIELD_BAD)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}

int input_beach_time_travel(int *time_travel)
{
    printf("Введите время путешествия в минутах, не больше %d, не меньше 1\n",
           MAX_TIME_TRAVEL);
    int rc = scanf("%d", time_travel);
    fgetc(stdin);
    if (rc != 1)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }
    rc = check_field_beach_time_travel(*time_travel);
    if (rc == CHECK_FIELD_BAD)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}

int input_sport_main_type(char main_type[MAX_STRING_FIELD_LEN])
{
    int len = 0, answer = 0, rc = 0;
    char variants[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
    get_variants_value_by_key('p', &len, variants);

    printf("Введите номер вида спорта в списке:\n");

    for (int i = 0; i < len; i++)
    {
        printf("%d. %s\n", i + 1, variants[i]);
    }
    rc = scanf("%d", &answer);
    fgetc(stdin);
    if (rc != 1 || answer > len || answer < 1)
    {
        printf("Некорректный ввод\n");
        return INPUT_ERROR;
    }
    strcpy(main_type, variants[answer - 1]);
    return INPUT_OK;
}

int input_sport_min_price(long int *min_price)
{
    printf("Введите минимальную цену путевки, не меньше 0, не больше %d\n",
           MAX_SPORT_MIN_PRICE);
    int rc = scanf("%ld", min_price);
    fgetc(stdin);
    if (rc != 1)
    {
        printf("Ввод не корректен\n");
        return INPUT_ERROR;
    }
    rc = check_field_sport_min_price(*min_price);
    if (rc == CHECK_FIELD_BAD)
    {
        printf("Ввод не корректен\n");
    }
    return INPUT_OK;
}

int input_country(countries *elem, countries table[MAX_STRUCT_COUNT], int len)
{
    int rc = 0;
    rc = input_name(elem->name, table, len);
    if (rc != INPUT_OK)
        return rc;
    rc = input_people_amount(&(elem->people_amount));
    if (rc != INPUT_OK)
        return rc;
    rc = input_capital(elem->capital);
    if (rc != INPUT_OK)
        return rc;
    rc = input_mainland(elem->mainland);
    if (rc != INPUT_OK)
        return rc;
    rc = input_tourism_type(elem->tourism_type);
    if (rc != INPUT_OK)
        return rc;
    if (strcmp(elem->tourism_type, "excursion") == 0)
    {
        rc = input_excursion_main_type(elem->description.excursion.main_type);
        if (rc != INPUT_OK)
            return rc;
        rc = input_excursion_monuments_count(&(elem->description.excursion.monument_count));
        if (rc != INPUT_OK)
            return rc;
    }
    if (strcmp(elem->tourism_type, "beach") == 0)
    {
        rc = input_beach_season(elem->description.beach.season);
        if (rc != INPUT_OK)
            return rc;
        rc = input_beach_temperature_air(&(elem->description.beach.temperature_air));
        if (rc != INPUT_OK)
            return rc;
        rc = input_beach_temperature_water(&(elem->description.beach.temperature_water));
        if (rc != INPUT_OK)
            return rc;
        rc = input_beach_time_travel(&(elem->description.beach.time_travel));
        if (rc != INPUT_OK)
            return rc;
    }
    if (strcmp(elem->tourism_type, "sport") == 0)
    {
        rc = input_sport_main_type(elem->description.sport.type_sport);
        if (rc != INPUT_OK)
            return rc;
        rc = input_sport_min_price(&(elem->description.sport.min_price));
        if (rc != INPUT_OK)
            return rc;
    }
    return INPUT_OK;
}


int input_filters_fields(char mainland[MAX_STRING_FIELD_LEN],
                          char sport_type[MAX_STRING_FIELD_LEN])
{
    int rc = 0;
    rc = input_mainland(mainland);
    if (rc != INPUT_OK)
        return rc;

    rc = input_sport_main_type(sport_type);
    if (rc != INPUT_OK)
        return rc;
    return INPUT_OK;
}
