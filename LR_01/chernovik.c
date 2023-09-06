
// Функция читает данные (мантиссу) из потока,
// По окончании может возвратить:
// INOUT_ERROR_BAD_LINE - ошибка при чтении мантиссы, неожиданные символы
// INOUT_END_READING - чтение мантиссы прошло успешно и порядка не будет (поплася в конце символ \n)
// INOUT_OK - если чтение потока не завершено (т.е. не было \n) и чтение мантиссы прошло успешно
/*
int read_mantissa(FILE *file, fns *number)
{
    int i = 0;
    char symbol = fgetc(file);
    if (symbol == '-')
        number->sign = -1;
    else
        number->sign = 1;

    if (symbol == '-' || symbol == '+' || symbol == ' ')
    {
        i++;
        symbol = fgetc(file);
    }

    while (symbol != '\n')
    {
        //printf("symbol = %c, i = %d\n", symbol, i);
        if (symbol == ' ')
        {
            symbol = fgetc(file);
            continue;
        }
        if (symbol == 'e' || symbol == 'E')
        {
            break;
        }

        if (strchr(DIGITS, symbol) != NULL || symbol == '.')
        {
            number->mantissa[i] = symbol;
            i++;
        }
        number->mantissa_len = i;

        if (strchr(DIGITS, symbol) == NULL && symbol != '.')
            return INOUT_ERROR_BAD_LINE;
        if (i > MAX_MANTISSA_LEN)
            return INOUT_ERROR_LONG_MANTISSA;
        symbol = fgetc(file);
    }

    if (symbol == '\n')
        return INOUT_END_READING;

    //printf("%c\n", symbol);


    return INOUT_OK;
}

int read_order(FILE *file, fns *number)
{
    int rc = fscanf(file, "%ld", &(number->order));
    if (rc != 1)
    {
        return INOUT_ERROR_BAD_LINE;
    }
    if (number->order > 99999 || number->order < -99999)
        return INOUT_ERROR_LONG_ORDER;
    return INOUT_OK;
}

int read_first_number(FILE *file, fns *number)
{
    int rc = INOUT_OK;
    char symbol = 0;

    rc = read_mantissa(file, number);
    //printf("\n rc = %d \n", rc);

    switch (rc) {
    case INOUT_OK:
        break;
    case INOUT_END_READING:
        return INOUT_OK;
    default:
        return rc;
    }

    rc = read_order(file, number);
    //printf("\n rc = %d \n", rc);


    switch (rc) {
    case INOUT_OK:
        break;
    default:
        return rc;
    }
    symbol = fgetc(file);
    if (symbol != '\n')
        return INOUT_ERROR_BAD_LINE;

    return INOUT_OK;
}

int read_second_number(FILE *file, sns *number)
{
    int i = 0;
    char symbol = fgetc(file);

    if (symbol == '-')
        number->sign = -1;
    else
        number->sign = 1;

    if (symbol == '-' || symbol == '+' || symbol == ' ')
    {
        i++;
        symbol = fgetc(file);
    }
    printf("symbol = %c, i = %d\n", symbol, i);

    while (symbol != '\n')
    {

        if (strchr(DIGITS, symbol) != NULL)
        {
            number->mantissa[i] = symbol;
            i++;
        }
        printf("symbol = %c, i = %d\n", symbol, i);
        number->mantissa_len = i;

        if (strchr(DIGITS, symbol) == NULL)
            return INOUT_ERROR_BAD_LINE;
        if (i > MAX_MANTISSA_LEN)
            return INOUT_ERROR_LONG_MANTISSA;
        symbol = fgetc(file);
    }
    number->mantissa_len = i;
    return INOUT_OK;
}*/


















void output_first_number(FILE *file, fns number)
{
    if (number.sign == 1)
    {
        fprintf(file, "+");
    }
    if (number.sign == -1)
    {
        fprintf(file, "-");
    }

    for (int i = 0; i < number.mantissa_len; i++)
    {
        fprintf(file, "%c", number.mantissa[i]);
    }
    fprintf(file, " E %ld\n", number.order);
    //printf("mantissa_len == %d\n", number.mantissa_len);
}









/*
int read_mantissa(char input_string[], num *first_num, int *end_i, int max_len)
{
    int i = *end_i, start_i = 0;
    char GOOD_END_SYMBOLS[] = " \nEe";
    if (input_string[i] == '-')
    {
        first_num->mantissa[i] = '-';
        i++;
        start_i = i;
    }
    else
    {
        first_num->mantissa[i] = '+';
    }
    if (input_string[i] == '+' || (input_string[i] == ' '))
    {
        i++;
        start_i = i;
    }

    while (strchr(GOOD_END_SYMBOLS, first_num->mantissa[i]) == NULL)
    {
        if (strchr(DIGITS, first_num->mantissa[i]) != NULL)
        {
            return INOUT_ERROR_MANTISSA;
        }
        if (i > max_len + start_i)
        {
            return INOUT_ERROR_LONG_MANTISSA;
        }
        first_num->mantissa[i] = input_string[i];
        i++;
    }

    if (input_string[i] == '\n')
    {
        return INOUT_OK;
    }
    i++;

    if (input_string[i] == 'E' || (input_string[i] == 'e'))
    {
        i++;
    }

    if (input_string[i] == ' ')
    {
        i++;
    }

    *end_i = i;

    return INOUT_OK;
}

int read_first_number(FILE *stream, num first_num)
{
    //int len_input_string = MAX_MANTISSA_LEN + 7 + MAX_ORDER_LEN;
    char input_string[MAX_MANTISSA_LEN + 7 + MAX_ORDER_LEN];
    int rc = INOUT_OK;
    void *res = fgets(input_string, MAX_MANTISSA_LEN + 7 + MAX_ORDER_LEN, stream);
    int start_i = 0;
    if (res == NULL)
    {
        return INOUT_ERROR_BAD_LINE;
    }
    rc = read_mantissa(input_string, &first_num, &start_i, MAX_MANTISSA_LEN);
    if (rc != INOUT_OK)
    {
        return rc;
    }
    rc = read_mantissa(input_string, &first_num, &start_i, MAX_ORDER_LEN);

    return rc;
}*/



















































/*
int check_digits(int digits[MAX_MANTISSA_LEN + 2], int number_len)
{
    int j = 0;
    for (int i = 0; i < number_len; i++)
    {
        if (digits[i] == -1)
        {
            j++;
        }
    }
    //printf("%d", j);
    if (j == 1)
    {
        return INOUT_OK;
    }
    return INOUT_WITHOUT_POINT;
}

int read_input(FILE *stream, int digits[MAX_MANTISSA_LEN + 2], int *number_len, int *order)
{
    char symbol[2] = "0";
    int i = 0, rc;

    while (fgets(symbol, 2, stream))
    {
        //printf("%s %d ", symbol, strcmp(symbol, " "));
        if (strchr(DIGITS, (int)(symbol[0])))
        {
            digits[i] = atoi(symbol);
            i++;
        }
        if (strcmp(symbol, ".") == 0)
        {
            digits[i] = -1;
            i++;
        }
        if (strcmp(symbol, " ") == 0 || strcmp(symbol, "\n") == 0)
        {
            break;
        }
        if ((strchr(DIGITS, (int)(symbol[0])) == NULL) && !(strcmp(symbol, ".") == 0))
        {
            //printf("ERROR");
            return INOUT_ERROR_BAD_LINE;
        }
        if (i > MAX_MANTISSA_LEN + 1)
        {
            return INOUT_ERROR_LONG_MANTISSA;
        }
    }
    *number_len = i;

    rc = check_digits(digits, *number_len);
    if (rc == INOUT_WITHOUT_POINT)
    {
        return rc;
    }

    rc = fscanf(stream, "%1s", symbol);
    //printf("rc = %d, symbol = %s\n", rc, symbol);
    if (rc == 0 || (strcmp(symbol, "\n") == 0))
    {
        //printf("rc = %d, strcmp(symbol, \"\\n\") = %d\n", rc, strcmp(symbol, "\n"));
        *order = 1;
        return INOUT_OK;
    }

    if ((strcmp(symbol, "E") == 0) || (strcmp(symbol, "e") == 0))
    {
        //printf("READ_NUM\n");
        fscanf(stream, "%d", order);
        if (*order > 99999 || *order < -99999)
        {
            return INOUT_ERROR_LONG_ORDER;
        }
    }
    else
    {
        //printf("End\n");
        return INOUT_ERROR_BAD_LINE;
    }
    return INOUT_OK;
}

int read_second_num(FILE *stream, int *second_num)
{
    int j = 0;
    for (int i = 0; i < number_len; i++)
    {
        if (digits[i] == -1)
        {
            j++;
        }
    }
    //printf("%d", j);
    if (j == 1)
    {
        return INOUT_OK;
    }
    return INOUT_WITHOUT_POINT;
}
int output_string(FILE *stream, int digits[MAX_MANTISSA_LEN + 2], int number_len, int order)
{
    for (int i = 0; i < number_len; i++)
    {
        if (digits[i] == -1)
        {
            fprintf(stream, ".");
        }
        else
        {
            fprintf(stream, "%d", digits[i]);
        }
    }
    printf(" E %d\n", order);
    fprintf(stream, "\n");
    return INOUT_OK;
}

*/


/*
void move_digits_to_right(char mantissa[MAX_MANTISSA_LEN], int len)
{
    char buf1 = 0, buf2 = 0;
    for (int i = 0; i < len; i++)
    {
        buf2 = mantissa[i];
        mantissa[i] = buf1;
        buf1 = buf2;
    }
}

void delete_start_zeros(char mantissa[])
{
    int len = strlen(mantissa);
    for (int i = 0; i > len; i++)
    {
        if (mantissa[i] != '0')
        {
            return;
        }
        move_digits_to_right(mantissa, len);
    }
}

int found_point(char mantissa[MAX_MANTISSA_LEN], int len)
{
    int index = len;
    for (int i = 0; i < len; i++)
    {
        if (mantissa[i] == '.')
        {
            index = i;
        }
    }
    return index;
}

// Функция сдвигает строку на 1 символ влево и добавляет порядок
void my_round(char string[], long int *order)
{
    int len = strlen(string);
    *order += 1;
    int digit = my_char_to_int(string[0]);
    int transfer = 0;
    //string[0] = my_int_to_char(digit, &transfer);
    if (digit > 4)
        transfer = 1;
    else
        transfer = 0;
    for (int i = 0; i < len; i++)
    {
        //printf("i = %d, digit = %d, transfer = %d\n", i, digit, transfer);
        digit = my_char_to_int(string[i + 1]) + transfer;
        printf("i = %d, digit = %d, transfer = %d, string[i-1] = %c, string[i] = %c\n", i, digit, transfer, string[i - 1], string[i]);
        string[i] = my_int_to_char(digit, &transfer);
        //printf("i = %d, digit = %d, transfer = %d, mantissa = %c\n", i, digit, transfer, string[i]);
    }
}

int recursion()
{
    return 0;
}

void multiply_sign(char s1, char s2, char *s3)
{
    if (s1 == s2)
        *s3 = '+';
    else
        *s3 = '-';
}

void output_intermediate_result(char *res)
{
    int n = strlen(res);
    for (int i = 0; i < n; i++)
    {
        printf("%c", res[i]);
    }
    printf("\n");
}

void sdvig(long int *order, int *k, char string[], int *order_transfer)
{
    int digit = 0, transfer = 0;
    int len = strlen(string);
    printf("len = %d\n", len);
    (*k)--;
    (*order)++;

    digit = my_char_to_int(string[0]);
    if (digit > 4)
    {
        transfer = 1;
    }

    for (int i = 1; i < len; i++)
    {
        output_intermediate_result(string);
        digit = my_char_to_int(string[i]) + transfer;
        transfer = 0;
        string[i-1] = my_int_to_char(digit, &transfer);
        printf("i = %d, digit = %d, transfer = %d, string[i-1] = %c, string[i] = %c\n", i, digit, transfer, string[i - 1], string[i]);
    }
    output_intermediate_result(string);
    printf("transfer = %d\n", transfer);
    (*order_transfer) = (*order_transfer) + transfer;
    string[len-1] = 0; //my_int_to_char(transfer, &transfer);
    printf("transfer = %d\n", transfer);
    \   output_intermediate_result(string);
}

int multiplicate(fns first_num, sns second_num, fns *answer)
{
    char intermediate_result[MAX_MANTISSA_LEN + 2]= {0};
    int order_transfer = 0;
    int first_digit, second_digit, result_digit;
    int k = 0;

    int len_2 = strlen(second_num.mantissa), len_1 = strlen(first_num.mantissa);
    long int order = first_num.order;

    for (int i = 0; i < len_2; i++)
    {
        second_digit = my_char_to_int(second_num.mantissa[i]);
        for (int j = 0; j < len_1; j++)
        {
            printf("i = %d, j = %d\n", i, j);
            first_digit = my_char_to_int(first_num.mantissa[j]);
            result_digit = first_digit * second_digit + order_transfer;
            printf("first_digit = %d, second_digit = %d, result_digit = %d\n", first_digit, second_digit, result_digit);

            intermediate_result[k] = my_int_to_char(result_digit, &order_transfer);
            k++;

            if (k == MAX_MANTISSA_LEN + 1)
            {
                printf("round!!\n");
                sdvig(&order, &k, intermediate_result, &order_transfer);
            }

            printf("%d\n", result_digit);
            // Если чисел больше 30, сдвиг цифр влево и увеличение порядка
            printf("first_num = ");
            output_intermediate_result(first_num.mantissa);
            printf("second_num = ");
            output_intermediate_result(second_num.mantissa);
            printf("k = %d, intermediate_result = ", k);
            output_intermediate_result(intermediate_result);
        }
        k = i + 1;
    }

    if (order_transfer != 0)
    {
        sdvig(&order, &k, intermediate_result, &order_transfer);
        intermediate_result[k] = my_int_to_char(order_transfer, &order_transfer);

    }

    delete_start_zeros(intermediate_result);
    strcpy(answer->mantissa, intermediate_result);
    multiply_sign(first_num.sign, second_num.sign, &(answer->sign));
    answer->order = order;
    return MULTIPLICATE_OK;
}
*/
