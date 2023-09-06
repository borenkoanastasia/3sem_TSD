#include "../../inc/file.h"

int read_field_char(FILE *file, char field[MAX_STRING_FIELD_LEN]);
int read_exursion_struct(FILE *file, excursion *line);
int read_beach_struct(FILE *file, beach_front *line);
int read_sport_struct(FILE *file, sport *line);
int read_line(FILE *file, countries *line);

int read_file_to_struct(char *filename, countries arr[MAX_STRUCT_COUNT], int *len)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return FILEWORK_ERROR_NO_FILE;

    int cur_index = 0;
    int rc = 0;

    //printf("%d\n", !feof(file));
    while (!feof(file))
    {
        rc = read_line(file, &(arr[cur_index]));
        //printf("%d\n", rc);
        if (rc != FILEWORK_OK)
            return rc;
        cur_index++;
        *len = cur_index;
    }
    *len = cur_index;
    rc = check_table_by_name(arr, *len);

    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_BAD_NAME;

    return FILEWORK_OK;
}

int read_line(FILE *file, countries *line)
{
    int rc = 0;
    char sym;

    rc = read_field_char(file, line->name);
    if (rc != FILEWORK_OK)
        return FILEWORK_ERROR_NAME;
    if (strlen(line->name) > MAX_NAME_LEN)
        return FILEWORK_ERROR_NAME;

    rc = fscanf(file, "%llu", &(line->people_amount));
    if (rc != 1)
        return FILEWORK_ERROR_PEOPLE_AMOUNT;
    rc = check_field_people_amount(line->people_amount);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_PEOPLE_AMOUNT;

    sym = fgetc(file);
    if (sym != '\t')
        return FILEWORK_ERROR_READING;

    rc = read_field_char(file, line->capital);
    if (rc != FILEWORK_OK)
        return FILEWORK_ERROR_CAPITAL;
    rc = check_field_capital(line->capital);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_CAPITAL;

    rc = read_field_char(file, line->mainland);
    if (rc != FILEWORK_OK)
        return FILEWORK_ERROR_MAINLAND;
    rc = check_field_mainland(line->mainland);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_MAINLAND;

    rc = read_field_char(file, line->tourism_type);
    if (rc != FILEWORK_OK)
        return FILEWORK_ERROR_TOURISM_TYPE;
    rc = check_field_tourism_type(line->tourism_type);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_TOURISM_TYPE;


    if (strcmp(line->tourism_type, "excursion") == 0)
        rc = read_exursion_struct(file, &(line->description.excursion));
    if (strcmp(line->tourism_type, "beach") == 0)
        rc = read_beach_struct(file, &(line->description.beach));
    if (strcmp(line->tourism_type, "sport") == 0)
        rc = read_sport_struct(file, &(line->description.sport));

    sym = fgetc(file);
    if (sym != '\n')
        return FILEWORK_ERROR_READING;

    return FILEWORK_OK;
}

// Функции читающие структуры разных типов
int read_exursion_struct(FILE *file, excursion *line)
{
    int rc = 0;

    rc = read_field_char(file,  line->main_type);
    if (rc != FILEWORK_OK)
        return FILEWORK_ERROR_READING;
    rc = check_field_exursion_main_type(line->main_type);
    //printf("rc = %d\n", rc);
    if (rc == CHECK_FIELD_BAD)
    {
        //printf("rc = %d\n", rc);
        return FILEWORK_ERROR_EXCURSION_MAIN_TYPE;}

    rc = fscanf(file, "%ld", &(line->monument_count));
    //printf("rc = %d\n", rc);
    if (rc == 1)
        return FILEWORK_ERROR_READING;
    rc = check_field_exursion_monument_count(line->monument_count);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_EXCURSION_MONUMENT_AMOUNT;

    return FILEWORK_OK;
}

int read_beach_struct(FILE *file, beach_front *line)
{
    int rc = 0;

    rc = read_field_char(file,  line->season);
    if (rc != FILEWORK_OK)
        return FILEWORK_ERROR_READING;
    rc = check_field_beach_season(line->season);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_BEACH_SEASON;

    rc = fscanf(file, "%d\t%d\t%d", &(line->temperature_air), &(line->temperature_water),
           &(line->time_travel));
    if (rc != 3)
        return FILEWORK_ERROR_READING;

    rc = check_field_beach_temperature_air(line->temperature_air);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_BEACH_TEMPERATURE_AIR;
    rc = check_field_beach_temperature_water(line->temperature_water);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_BEACH_TEMPERATURE_WATER;
    rc = check_field_beach_time_travel(line->time_travel);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_BEACH_TIME_TRAVEL;

    return FILEWORK_OK;
}

int read_sport_struct(FILE *file, sport *line)
{
    int rc = 0;

    rc = read_field_char(file, line->type_sport);
    if (rc != FILEWORK_OK)
        return FILEWORK_ERROR_READING;
    rc = check_field_sport_type(line->type_sport);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_SPORT_TYPE;

    rc = fscanf(file, "%ld", &(line->min_price));
    if (rc != 1)
        return FILEWORK_ERROR_READING;
    rc = check_field_sport_min_price(line->min_price);
    if (rc == CHECK_FIELD_BAD)
        return FILEWORK_ERROR_SPORT_MIN_PRICE;

    return FILEWORK_OK;
}

// Читает поле типа char из file в field и возвращает код завершения
int read_field_char(FILE *file, char field[MAX_STRING_FIELD_LEN])
{
    int cur_index = 0;
    char symbol = fgetc(file);
    //printf("\n");

    while (symbol != '\t')
    {
        //printf("%c\n", symbol);
        if (cur_index == MAX_STRING_FIELD_LEN)
        {
            //printf("cur_index = %d\n",cur_index);
            return FILEWORK_ERROR_LONG_FIELD;
        }
        field[cur_index] = symbol;
        cur_index++;
        symbol = fgetc(file);
    }
    field[cur_index] = 0;
    return FILEWORK_OK;
}
