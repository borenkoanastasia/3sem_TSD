#include "input_output.h"

// Функция читает данные (мантиссу) из потока,
// По окончании может возвратить:
// INOUT_ERROR_BAD_LINE - ошибка при чтении мантиссы, неожиданные символы
// INOUT_END_READING - чтение мантиссы прошло успешно и порядка не будет (поплася в конце символ \n)
// INOUT_OK - если чтение потока не завершено (т.е. не было \n) и чтение мантиссы прошло успешно

void delete_end_zeros(char mantissa[], int point_pos)
{
    int len = strlen(mantissa);
    for (int i = len - 1; i > 0; i--)
    {
        if (point_pos == -1)
        {
            break;
        }
        if (point_pos == i)
        {
            break;
        }
        if (mantissa[i] == '0')
        {
            mantissa[i] = 0;
        }
        if (mantissa[i] != '0')
        {
            break;
        }
    }
}

int read_order(FILE *file, long int *order)
{
    int rc = fscanf(file, "%ld", order);
    if (rc != 1)
    {
        return INOUT_ERROR_BAD_LINE;
    }
    if (*order > 99999 || *order < -99999)
        return INOUT_ERROR_LONG_ORDER;
    return INOUT_OK;
}

// point_pos - указывает на цифру перед которой идет точка)
// end - возможные окончания мантисы
int read_mantissa(char mantissa[], char *sign, int *point_pos, char *end)
{
    char symbol = fgetc(stdin);
    char flag = '0';
    int i = 0;
    *point_pos = -1;
    *sign = 0;

    // Обработка +- в начале мантисы: +100 или -100
    if (symbol == '-' || symbol == '+')
    {
        *sign = symbol;
        symbol = fgetc(stdin);
    }
    if (*sign == 0)
    {
        *sign = '+';
    }

    //printf("symbol = %c\n", symbol);

    while (!strchr(end, symbol))
    {
        // Вспомогательный вывод
        //printf("symbol = %c, flag = %c, i = %d\n", symbol, flag, i);
        // Отбрасывание не важных нулей
        if ((flag == '0') && (symbol == '0') && (*point_pos == -1))
        {
            symbol = fgetc(stdin);
            continue;
        }

        // Пропуск всех пробелов в числе
        if (symbol == ' ')
        {
            symbol = fgetc(stdin);
            continue;
        }

        // Обработка точки
        if (symbol == '.' && *point_pos == -1)
        {
            if (i == 0)
            {
                mantissa[i] = '0';
                i++;
            }
            *point_pos = i + 1;
            symbol = fgetc(stdin);
            continue;
        }

        // Проверка, чтобы символ был числом
        if (DIGITS(symbol) == NULL)
        {
            //printf("NOT DIGIT\n");
            return INOUT_ERROR_BAD_LINE;
        }

        mantissa[i] = symbol;

        flag = '1';
        i++;
        if (i > MAX_MANTISSA_LEN)
        {
            return INOUT_ERROR_LONG_MANTISSA;
        }
        symbol = fgetc(stdin);
    }

    // Проверка мантиссы на пустоту
    if (i == 0)
    {
        mantissa[i] = '0';
        i++;
    }

    // Добавление 0 в конец строки мантиссы
    mantissa[i] = 0;
    i++;

    // Удаление не значащих нулей после точки 10.2500
    delete_end_zeros(mantissa, *point_pos);

    if (symbol == '\n')
    {
        return INOUT_OK;
    }

    return INOUT_NOT_END_READING;
}

void reverse_copy_mantissa(char from_t[], char to_t[]) //t - thing
{
    int len = strlen(from_t);
    for (int i = 0; i < len; i++)
    {
        //printf("i = %d, len = %d\n", i, len);
        to_t[i] = from_t[len - i - 1];
    }
    to_t[len] = 0;
}

int read_first_number(fns *first_num)
{
    char end[] = "Ee\n";
    int rc, point_pos = 0;
    char mantissa[MAX_MANTISSA_LEN + 1] = {0};

    rc = read_mantissa(mantissa, &(first_num->sign), &point_pos, end);

    reverse_copy_mantissa(mantissa, first_num->mantissa);
    //printf("%d", (int)strlen(mantissa));
    //printf("%d", (int)strlen(first_num->mantissa));

    if (rc != INOUT_NOT_END_READING)
    {
        return rc;
    }
    rc = read_order(stdin, &(first_num->order));
    //printf("before first_num.order = %ld\n", first_num->order);
    if (point_pos != -1)
    {
        first_num->order -= (point_pos - 1);
    }
    //printf("point_pos = %d\n", point_pos);
    //printf("after first_num.order = %ld\n", first_num->order);
    char symbol = fgetc(stdin);
    if (symbol != '\n')
    {
        return INOUT_ERROR_BAD_LINE;
    }
    if (rc != INOUT_OK)
    {
        return rc;
    }

    return INOUT_OK;
}

int read_second_number(sns *second_num)
{
    //printf("start read second number\n");
    char end[] = "\n";
    int rc, point_position;
    char mantissa[MAX_MANTISSA_LEN + 1] = {0};
    rc = read_mantissa(mantissa, &(second_num->sign), &(point_position), end);
    if (point_position != -1)
    {
        return INOUT_ERROR_BAD_LINE;
    }
    reverse_copy_mantissa(mantissa, second_num->num);
    if (rc != INOUT_NOT_END_READING)
    {
        return rc;
    }
    return INOUT_OK;
}

int check_zero(char mantissa[MAX_MANTISSA_LEN + 1])
{
    int len = strlen(mantissa);
    for (int i = 0; i < len; i++)
    {
        if (mantissa[i] != '0')
            return 0;
    }
    return 1;
}

int get_mantissa_len(char mantissa[MAX_MANTISSA_LEN + 1])
{
    int len = strlen(mantissa), res = 0;
    int k = 0;
    for (int i = 0; i < len; i++)
    {
        if (mantissa[i] != '0')
            k = 1;
        if (k == 1)
            res += 1;
    }
    k = 0;
    for (int i = len; i > 0; i--)
    {
        if (mantissa[i] != '0')
            k = 1;
        if (k == 1)
            res -= 1;
    }
    return res;
}

void output_mantissa(char *res)
{
    int n = strlen(res);
    for (int i = 0; i < n; i++)
    {
        printf("%c", res[i]);
    }
    printf("\n");
}

int output_first_number(fns number)
{
    int n = get_mantissa_len(number.mantissa);
    //output_mantissa(number.mantissa);
    //printf("order = %ld\n", number.order);
    long int order = number.order + n;
    //printf("order = %ld\n", order);
    if (order > 100000 || order < -100000)
    {
        return INOUT_ERROR_LONG_ORDER_CALC;
    }
    //printf("n = %d, num_order = %ld\n", n, number.order);

    int r = check_zero(number.mantissa);

    if (r == 1)
    {
        number.mantissa[0] = '0';
        number.mantissa[1] = '0';
        number.mantissa[2] = 0;
        order = 0;
    }
    //printf("n = %d, num_order = %ld, rc = %d\n", n, order, r);
    printf("Результат умножения:\n");
    printf("%c0.", number.sign);
    int len = strlen(number.mantissa);
    for (int i = 0; i < MAX_MANTISSA_LEN + 1; i++)
    {
        if (i <= len)
        {
            printf("%c", number.mantissa[len - i - 1]);
        }
        else
        {
            printf("0");
        }
    }
    printf(" E %ld\n", order);
    //printf("mantissa_len == %d\n", number.mantissa_len);
    return INOUT_OK;
}

void output_error_message(int rc)
{
    switch(rc)
    {
    case INOUT_ERROR_BAD_LINE:
        printf("Некорректный ввод\n");
        break;
    case INOUT_ERROR_LONG_ORDER:
        printf("Превышение порядка при вводе\n");
        break;
    case INOUT_ERROR_LONG_MANTISSA:
        printf("Превышение мантиссы при вводе\n");
        break;
    case INOUT_ERROR_EMPTY_MANTISSA:
        printf("Пустая мантисса при вводе\n");
        break;
    case INOUT_ERROR_LONG_ORDER_CALC:
        printf("Превышение порядка при вычислениях\n");
        break;
    }
}

void output_second_num(sns first_num)
{
    //printf("mantissa_len = %d\n", first_num.mantissa_len);
    printf("%c", first_num.sign);
    int n = strlen(first_num.num);
    for (int i = 0; i < n; i++)
    {
        printf("%c", first_num.num[n - 1 - i]);
    }
    printf("\n");
}

void output_start_first_num_message()
{
    printf("Программа выполняет умножение действительного числа на целое.\n");
    printf("Формат действительного числа: \n[знак][мантисса - до 30 знаков][E порядок до 5 знаков]\n");
    printf("Формат целого числа: \n[знак][мантисса - до 30 знаков]\n");
    printf("Примечания для ввода:\n");
    printf("\t - В случае если введена пустая строка, считается что число рано 0\n");
    printf("\t - Ведущих нулей в мантиссе может быть сколько угодно\n");
    printf("\n");
    printf("Введите действительное число:\n");
    printf("|           mantissa           | E |order|\n");
    printf("________________________________\n");
}

void output_start_second_num_message()
{
    printf("Введите целое число:\n");
    printf("|           mantissa           |\n");
    printf("________________________________\n");
}
