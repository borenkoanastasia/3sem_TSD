#include "../inc/menu.h"
#include "../inc/check_fields.h"
#include "../inc/key_array.h"
#include "../inc/struct_array.h"
#include "../inc/help_functions.h"
#include "../inc/testing.h"
#include "../inc/file.h"

void output_start_message()
{
    printf("Программа работает с таблицей стран.\n");
    printf("Файл, который будет проанализирован: table_file.txt\n");
    printf("Таблица написана и заполнена на английком.");
    printf("Все ее дополнения должны быть тоже на английком.");
}

void output_menu_message()
{
    //int variants_count = 0;
    char comment_string[] = "     ";
    char dash_string[COMMAND_STRING_LEN];
    for (int i = 0; i < COMMAND_STRING_LEN; i++)
    {
        dash_string[i] = '-';
    }
//\x1b[1;31m
    printf("\%40.40s МЕНЮ %40.40s\n", dash_string, dash_string);
    printf("%s 1.Вывести таблицу\n", comment_string);
    printf("%s 2.Добавить страну в таблицу\n", comment_string);
    printf("%s 3.Удалить страну из таблицы\n", comment_string);
    //printf("%s 4.Изменить страну в таблице\n", comment_string);
    printf("%s 4.Сортировать быстрой сортировкой по ключу\n", comment_string);
    printf("%s 5.Сортировать сортировкой пузырьком по ключу\n", comment_string);
    printf("%s 6.Протестировать и сравнить сортировки (быструю и пузырьком) по времени\n", comment_string);
    printf("%s 7.Протестировать и сравнить быстрою сортировку всей таблицы и по ключам по памяти\n", comment_string);
    printf("%s 8.Протестировать и сравнить сортировку пузырьком всей таблицы и по ключам по памяти\n", comment_string);
    printf("%s -1.Выйти\n", comment_string);
    printf("\nДля выбора пункта меню, введите его номер в приведенном списке\n");
}

void add_country(countries table[MAX_STRUCT_COUNT], int *len)
{
    countries elem;

    printf("Введите через tab поля новой структуры в слудущем порядке:\n");
    printf("   'имя' 'население' 'столица' 'материк' 'основной вид турима'\n");
    printf("И в зависимости от основного типа туризма новой страны\n");
    printf("(excursion)   'основной вид экскурсий' 'кол-во памятников'\n");
    printf("(beach)       'основной сезон' 'температура воздуха' 'температура воды' %s",
           "'время полета до страны'\n");
    printf("(sport)       'основной вид спорта' 'минимальная стоимость отдыха'\n");
    int rc = read_line(stdin, &elem);
    filework_output_error_messages(rc);

    add_struct(table, len, elem);
}

int del_country()
{
    printf("Введите название страны\n");
    return 0;
}
int make_choise(int choise, countries table[MAX_STRUCT_COUNT], int *len)
{
    char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN];

    switch (choise) {
    case 1:
        output_table(table, *len);
        break;
    case 2:
        add_country(table, len);
        break;
    case 3:
        del_country();
        break;
    case 4:
        make_key_array_from_struct_array(arr, table, *len);
        key_array_sort(arr, *len);
        key_array_output_table(arr, table, *len);
        break;
    case 5:
        make_key_array_from_struct_array(arr, table, *len);
        key_array_quick_sort(arr, 0, *len);
        key_array_output_table(arr, table, *len);
        break;
    case 6:
        //add_country();
        break;
    case 7:
        //add_country();
        break;
    case 8:
        //add_country();
        break;
    case -1:
        return 1;
    }
    return 0;
}

void output_results_testing(int time, int memory);
void output_end_message();
