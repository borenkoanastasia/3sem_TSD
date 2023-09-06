#include "../../inc/file.h"
#include "../../inc/help_functions.h"

void filework_output_error_messages(int rc)
{
    switch (rc)
    {
    case FILEWORK_ERROR_NAME:{
        printf("Страна в файле имеет некорректное имя\n");
        break;
    }
    case FILEWORK_ERROR_PEOPLE_AMOUNT:{
        printf("Страна в файле имеет некорректную популяцию\n");
        printf("Population must belong to (%d, %ld)\n", 0, MAX_PEOPLE_AMOUNT);
        break;
    }
    case FILEWORK_ERROR_CAPITAL:{
        printf("Страна в файле имеет некорректную столицу\n");
        break;
    }
    case FILEWORK_ERROR_MAINLAND:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('m', &len, types);

        printf("Страна в файле имеет некорректный материк\n");
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

        printf("Страна в файле имеет некорректный тип туризма\n");
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

        printf("Страна в файле имеет некорректный тип экскурсионного туризма\n");
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
        printf("Страна в файле имеет некорректное кол-во памятников\n");
        printf("Monuments amount must belong to (%d, %d)\n", 0,
               MAX_EXURSION_MONUMENTS_COUNT);
        break;
    }
    case FILEWORK_ERROR_BEACH_SEASON:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('t', &len, types);

        printf("Страна в файле имеет некорректный пляжный сезон\n");
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
        printf("Страна в файле имеет некорректную температуру воздуха\n");
        printf("Температура воздуха должна принадлежать интервалу(%d, %d)\n",
               MIN_TEMPERATURE, MAX_TEMPERATURE);
        break;
    }
    case FILEWORK_ERROR_BEACH_TEMPERATURE_WATER:{
        printf("Страна в файле имеет некорректную температуру воды\n");
        printf("Температура воды должна принадлежать интервалу (%d, %d)\n", MIN_TEMPERATURE,
               MAX_TEMPERATURE);
        break;
    }
    case FILEWORK_ERROR_BEACH_TIME_TRAVEL:{
        printf("Страна в файле имеет некорректное время путешествия\n");
        printf("Время путешествия должно принадлежать интервалу (%d, %d)\n", 0,
               MAX_TIME_TRAVEL);
        break;
    }
    case FILEWORK_ERROR_SPORT_TYPE:{
        int len = 0;
        char types[MAX_AMOUNT_VARIANTS][MAX_STRING_FIELD_LEN];
        get_variants_value_by_key('t', &len, types);

        printf("Страна в файле имеет некорректный тип спортивного туризма\n");
        printf("Спортивный тип туризма должен быть вабран из списка и записан также %s",
               "как в списке:\n");

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
        printf("Страна в файле имеет некорректную минимальную стоимость путешестия\n");
        printf("Минимальная стоимость путешествия должна принадлежать интервалу (%d, %d)\n",
               0, MAX_SPORT_MIN_PRICE);
        break;
    }
    case FILEWORK_ERROR_READING:{
        printf("В заполнении таблицы есть ошибка\n");
        break;
    }
    case FILEWORK_ERROR_LONG_FIELD:{
        printf("Одно из полей слишком длинное\n");
        break;
    }
    case FILEWORK_ERROR_BAD_NAME:{
        printf("В файле две страны имеют одно имя\n");
        break;
    }
    }
}
