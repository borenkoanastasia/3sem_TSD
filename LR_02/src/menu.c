#include "../inc/menu.h"

void output_start_message()
{
    printf("Программа работает с таблицей стран.\n");
    printf("Файл, который будет проанализирован: table_file.txt\n");
    printf("Таблица написана и заполнена на английcком. ");
    printf("Все ее дополнения должны быть тоже на английском.\n");
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
    printf("%s 4.Сортировать сортировкой пузырьком по ключу\n", comment_string);
    printf("%s 5.Сортировать быстрой сортировкой по ключу\n", comment_string);
    printf("%s 6.Протестировать и сравнить сортировки\n", comment_string);
    printf("%s 7.Отфильтровать таблицу\n", comment_string);
    printf("%s 8.Сортировать таблицу и сохранить\n", comment_string);
    printf("\nДля выбора пункта меню, введите его номер в приведенном списке\n");
    printf("Ввод не из списка - завершение программы\n");
}

void output_table_testing(countries table[MAX_STRUCT_COUNT], int len)
{
    int t_k_s, t_k_q, t_s_s, t_s_q, t_max_k = 0, t_max_t = 0;
    int m_k_s, m_k_q, m_s_s, m_s_q, m_max_k = 0, m_max_t = 0;

    test_key_sort(table, len, &t_k_s, &m_k_s);
    test_key_quick_sort(table, len, &t_k_q, &m_k_q);
    test_struct_sort(table, len, &t_s_s, &m_s_s);
    test_struct_quick_sort(table, len, &t_s_q, &m_s_q);

    t_max_k = get_max(t_k_s, t_k_q);
    t_max_t = get_max(t_s_s, t_s_q);
    m_max_k = get_max(m_k_s, m_k_q);
    m_max_t = get_max(m_s_s, m_s_q);

    for (int i = 0; i < 68; i++)
    {
        printf("_");
    }
    printf("\n\n");
    printf("|%6s|%10s|%10d|%7d|%8d|%10.3f|%10.3f|\n", "key", "sort", len, t_k_s, m_k_s,
           (float)t_k_s * 100 / t_max_k, (float)m_k_s / m_max_k * 100);
    printf("|%6s|%10s|%10d|%7d|%8d|%10.3f|%10.3f|\n", "key", "quick sort", len, t_k_q, m_k_q,
           (float)t_k_q / t_max_k * 100, (float)m_k_q * 100 / m_max_k);
    for (int i = 0; i < 68; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("|%6s|%10s|%10d|%7d|%8d|%10.3f|%10.3f|\n", "table", "sort", len, t_s_s, m_s_s,
           (float)t_s_s / t_max_t * 100, (float)m_s_s * 100 / m_max_t);
    printf("|%6s|%10s|%10d|%7d|%8d|%10.3f|%10.3f|\n", "table", "quick sort", len, t_s_q,
           m_s_q, (float)t_s_q / t_max_t * 100, (float)m_s_q * 100 / m_max_t);
}

void output_testing(countries table[MAX_STRUCT_COUNT], int len)
{
    printf("Таблица с результатами тестирования (на английском)\n");
    printf("В колонках time %s и memory %s сравниваются между собой быстрая сортировка и %s %s",
           "%", "%", "сортировка пузырьком из значений для этих полей выбирается наибольшее и берется за 100,",
           "другое высчитывается относительно него\n");
    printf("|%6s|%10s|%10s|%7s|%8s|%10s|%10s|\n", "sorted", "sorting", "table", "time", "memory", "time",
           "memory");
    printf("|%6s|%10s|%10s|%7s|%8s|%10s|%10s|\n", "object", "type", "size", "seconds", "bytes", "\%", "\%");


    countries t1[MAX_STRUCT_COUNT];
    copy_countries(table, t1, len);
    output_table_testing(t1, len);
    output_table_testing(t1, len/2);
    output_table_testing(t1, len/4);
    output_table_testing(t1, len/8);
    for (int i = 0; i < 68; i++)
    {
        printf("_");
    }
    printf("\n\n");

    printf("Конец тестирования\n");
}

int make_choise(int choise, countries table[MAX_STRUCT_COUNT], int *len,
                char filename[MAX_FILENAME_LEN])
{
    key arr[MAX_STRUCT_COUNT];

    switch (choise) {
    case 1:
        output_table(table, *len);
        break;
    case 2:
        add_country(table, len);
        write_table_in_file(filename, table, *len);
        break;
    case 3:
        output_table(table, *len);
        del_country(table, len);
        write_table_in_file(filename, table, *len);
        break;
    case 4:
        make_key_array_from_struct_array(arr, table, *len);
        key_array_sort(arr, *len);
        key_array_output_table(arr, table, *len);
        break;
    case 5:
        make_key_array_from_struct_array(arr, table, *len);
        key_array_quick_sort(arr, 0, *len - 1);
        key_array_output_table(arr, table, *len);
        break;
    case 6:
        output_testing(table, *len);
        break;
    case 7:
        choice_filter(table, *len);
        break;
    case 8:
        struct_array_sort(table, *len);
        write_table_in_file(filename, table, *len);
        break;
    default:
        return 1;
    }
    return 0;
}
