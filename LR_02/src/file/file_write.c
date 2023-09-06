#include "../../inc/file.h"

void write_excursion_in_file(FILE *file, excursion line)
{
    fprintf(file, "%s\t", line.main_type);
    fprintf(file, "%ld", line.monument_count);
}

void write_beach_in_file(FILE *file, beach_front line)
{
    fprintf(file, "%s\t", line.season);
    fprintf(file, "%d\t", line.temperature_air);
    fprintf(file, "%d\t", line.temperature_water);
    fprintf(file, "%d", line.time_travel);
}

void write_sport_in_file(FILE *file, sport line)
{
    fprintf(file, "%s\t", line.type_sport);
    fprintf(file, "%ld", line.min_price);
}

void write_country_in_file(FILE *file, countries line)
{
    fprintf(file, "%s\t", line.name);
    fprintf(file, "%llu\t", line.people_amount);
    fprintf(file, "%s\t", line.capital);
    fprintf(file, "%s\t", line.mainland);
    fprintf(file, "%s\t", line.tourism_type);

    if (strcmp(line.tourism_type, "excursion") == 0)
    {
        write_excursion_in_file(file, line.description.excursion);
    }
    if (strcmp(line.tourism_type, "beach") == 0)
    {
        write_beach_in_file(file, line.description.beach);
    }
    if (strcmp(line.tourism_type, "sport") == 0)
    {
        write_sport_in_file(file, line.description.sport);
    }
    fprintf(file, "\n");
}

void write_table_in_file(char file_name[MAX_FILENAME_LEN], countries table[MAX_STRUCT_COUNT],
                   int len)
{
    FILE *file = fopen(file_name, "w");
    for (int i = 0; i < len; i++)
    {
        write_country_in_file(file, table[i]);
    }
    fclose(file);
}
