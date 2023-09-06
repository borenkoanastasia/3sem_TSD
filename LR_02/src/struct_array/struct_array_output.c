#include "../../inc/struct_array.h"
#include "../../inc/help_functions.h"

void output_excursion_tourism_type_line(excursion line)
{
    printf(" %10ld |", line.monument_count);
    printf(" %21.21s |", line.main_type);
}

void output_beach_front_tourism_type_line(beach_front line)
{
    printf(" %6.6s |", line.season);
    printf(" %3d |", line.temperature_air);
    printf(" %3d |", line.temperature_water);

    int h = 0, min = 0;
    make_hours_from_minutes(line.time_travel, &min, &h);
    printf(" %2d ч. %2d мин. |", h, min);
}

void output_sport_tourism_type_line(sport line)
{
    printf(" %21.21s |", line.type_sport);
    printf(" %10ld |", line.min_price);
}

void output_description(char tourism_type[MAX_STRING_FIELD_LEN], type_tourism description)
{
    if (strcmp(tourism_type, "excursion") == 0)
        output_excursion_tourism_type_line(description.excursion);
    if (strcmp(tourism_type, "beach") == 0)
        output_beach_front_tourism_type_line(description.beach);
    if (strcmp(tourism_type, "sport") == 0)
        output_sport_tourism_type_line(description.sport);
}

void output_countries_type(countries line)
{
    printf("| %25.25s ", line.name);
    printf("| %12llu ", line.people_amount);
    printf("| %20.20s ", line.capital);
    printf("| %15.15s ", line.mainland);
    printf("| %15.15s |", line.tourism_type);
    output_description(line.tourism_type, line.description);
}

void output_table(countries result[MAX_STRUCT_COUNT], int len)
{
    output_title();
    for (int i = 0; i < len; i++)
    {
        printf("| %2d ", i + 1);
        output_countries_type(result[i]);
        printf("\n");
    }
}

void output_title()
{
    printf("|  N | %25.25s | %12.12s | %20.20s | %15.15s | %15.15s | %34.34s |\n",
           "Country Name", "Population", "Capital", "Mainland", "Tourism type", "Details");

    for (int i = 0; i < 20 + 12 + 20 + 15 + 15 + 35 + 2 + 3 * 5 + 2 + 4; i++)
    {
        printf("-");
    }
    printf("\n");
}
