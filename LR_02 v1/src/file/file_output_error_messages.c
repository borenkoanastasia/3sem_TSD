#include "../../inc/file.h"
#include "../../inc/help_functions.h"

void filework_output_error_messages(int rc)
{
    switch (rc)
    {
    case FILEWORK_ERROR_NAME:{
        printf("The file contains a country with an incorrect name\n");
        break;
    }
    case FILEWORK_ERROR_PEOPLE_AMOUNT:{
        printf("The file contains a country with an incorrect population\n");
        printf("Population must belong to (%d, %ld)\n", 0, MAX_PEOPLE_AMOUNT);
        break;
    }
    case FILEWORK_ERROR_CAPITAL:{
        printf("The file contains a country with an incorrect capital\n");
        break;
    }
    case FILEWORK_ERROR_MAINLAND:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('m', &len, types);

        printf("The file contains a country with an incorrect mainland\n");
        printf("Mainland must belong to list:\n");

        for (int i = 0; i < len; i++)
        {
            printf("%s", types[i]);
            if (i != len)
                printf(", ");
        }
        printf("\n");
        break;
    }
    case FILEWORK_ERROR_TOURISM_TYPE:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('t', &len, types);

        printf("The file contains a country with an incorrect tourism type\n");
        printf("Tourism type must belong to list:\n");

        for (int i = 0; i < len; i++)
        {
            printf("%s", types[i]);
            if (i != len)
                printf(", ");
        }
        printf("\n");
        break;
    }
    case FILEWORK_ERROR_EXCURSION_MAIN_TYPE:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('t', &len, types);

        printf("The file contains a country with an incorrect excursion type\n");
        printf("Excursion type must belong to list:\n");

        for (int i = 0; i < len; i++)
        {
            printf("%s", types[i]);
            if (i != len)
                printf(", ");
        }
        printf("\n");
        break;
    }
    case FILEWORK_ERROR_EXCURSION_MONUMENT_AMOUNT:{
        printf("The file contains a country with an incorrect monuments amount\n");
        printf("Monuments amount must belong to (%d, %d)\n", 0,
               MAX_EXURSION_MONUMENTS_COUNT);
        break;
    }
    case FILEWORK_ERROR_BEACH_SEASON:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('t', &len, types);

        printf("The file contains a country with an incorrect beach season\n");
        printf("Beach season must belong to:\n");

        for (int i = 0; i < len; i++)
        {
            printf("%s", types[i]);
            if (i != len)
                printf(", ");
        }
        printf("\n");
        break;
    }
    case FILEWORK_ERROR_BEACH_TEMPERATURE_AIR:{
        printf("The file contains a country with an incorrect air temperature\n");
        printf("Air temperature must belong to (%d, %d)\n", MIN_TEMPERATURE,
               MAX_TEMPERATURE);
        break;
    }
    case FILEWORK_ERROR_BEACH_TEMPERATURE_WATER:{
        printf("The file contains a country with an incorrect water temperature\n");
        printf("Water temperature must belong to (%d, %d)\n", MIN_TEMPERATURE,
               MAX_TEMPERATURE);
        break;
    }
    case FILEWORK_ERROR_BEACH_TIME_TRAVEL:{
        printf("The file contains a country with an incorrect travel time\n");
        printf("Travel time must belong to (%d, %d)\n", 0, MAX_TIME_TRAVEL);
        break;
    }
    case FILEWORK_ERROR_SPORT_TYPE:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('t', &len, types);

        printf("The file contains a country with an incorrect sport type\n");
        printf("Sport type must belong to list:\n");

        for (int i = 0; i < len; i++)
        {
            printf("%s", types[i]);
            if (i != len)
                printf(", ");
        }
        printf("\n");
        break;
    }
    case FILEWORK_ERROR_SPORT_MIN_PRICE:{
        printf("The file contains a country with an %s",
               "incorrect min price of sport travel\n");
        printf("Price must belong to (%d, %d)\n", 0, MAX_SPORT_MIN_PRICE);
        break;
    }
    case FILEWORK_ERROR_READING:{
        printf("Table content is incorrect\n");
        break;
    }
    case FILEWORK_ERROR_LONG_FIELD:{
        printf("One of the fields exceeds the allowed size\n");
        break;
    }
    case FILEWORK_ERROR_BAD_NAME:{
        printf("In file two countries have one name\n");
        break;
    }
    }
}
