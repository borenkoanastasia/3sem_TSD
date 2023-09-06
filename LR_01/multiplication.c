#include "multiplication.h"

int my_char_to_int(char sym)
{
    int num = 10;
    switch (sym) {
        case '0': {num = 0; break;}
        case '1': {num = 1; break;}
        case '2': {num = 2; break;}
        case '3': {num = 3; break;}
        case '4': {num = 4; break;}
        case '5': {num = 5; break;}
        case '6': {num = 6; break;}
        case '7': {num = 7; break;}
        case '8': {num = 8; break;}
        case '9': {num = 9; break;}
        default: {num = 10;}
    }
    return num;
}

char my_int_to_char(int num, int *transfer)
{
    char sym = 0;
    switch (num%10) {
        case 0: {sym = '0'; break;}
        case 1: {sym = '1'; break;}
        case 2: {sym = '2'; break;}
        case 3: {sym = '3'; break;}
        case 4: {sym = '4'; break;}
        case 5: {sym = '5'; break;}
        case 6: {sym = '6'; break;}
        case 7: {sym = '7'; break;}
        case 8: {sym = '8'; break;}
        case 9: {sym = '9'; break;}
        default: {sym = 'a';}
    }
    *transfer = num / 10;
    return sym;
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

void multiplicate_line_and_symbol(char line[], char symbol, char result_line[MAX_MANTISSA_LEN + 1])
{
    int digit = my_char_to_int(symbol);
    int transfer = 0, cur_digit = 0, cur_result = 0;
    int line_len = strlen(line);
    //output_intermediate_result(line);
    for (int i = 0; i < line_len; i++)
    {
        cur_digit = my_char_to_int(line[i]);
        cur_result = cur_digit * digit + transfer;
        result_line[i] = my_int_to_char(cur_result, &transfer);
        //printf("transfer = %d, ", transfer);
        //output_intermediate_result(result_line);
    }
    if (transfer != 0)
    {
        result_line[line_len] = my_int_to_char(transfer, &transfer);
        result_line[line_len + 1] = 0;
        //output_intermediate_result(result_line);
    }
}

void my_plus_copy(int index_start, char copy_str[], char result_str[])
{
    int res_len = strlen(result_str);
    int digit = 0, transfer = 0, res_digit;
    int copy_line_len = strlen(copy_str);

    for (int i = index_start; i < (copy_line_len + index_start); i++)
    {
        if (res_len > i)
        {
            digit = my_char_to_int(result_str[i]) + transfer;
            res_digit = my_char_to_int(copy_str[i - index_start]) + digit;
            result_str[i] = my_int_to_char(res_digit, &transfer);
        }
        else if(transfer != 0)
        {
            res_digit = my_char_to_int(copy_str[i - index_start]) + transfer;
            result_str[i] = my_int_to_char(res_digit, &transfer);
        }
        else
        {
            result_str[i] = copy_str[i - index_start];
        }
        //output_intermediate_result(result_str);

    }
}

void move_digits(char result[])
{
    int result_len = strlen(result);
    int digit = my_char_to_int(result[0]), transfer = 0;
    if (digit > 4)
    {
        transfer = 1;
    }
    for (int i = 0; i < result_len - 1; i++)
    {
        if (transfer != 0)
        {
            digit = my_char_to_int(result[i + 1]) + transfer;
            result[i] = my_int_to_char(digit, &transfer);
        }
        else
        {
        result[i] = result[i + 1];
        }
        //output_intermediate_result(result);
    }
    result[result_len - 1] = 0;
}

void multiplicate_two_strings(char first_num[], char second_num[], char result_num[], int order_changes)
{
    //int first_len = strlen(first_num);
    int second_len = strlen(second_num);
    char buf[MAX_MANTISSA_LEN + 2] = { 0 };
    char result[MAX_MANTISSA_LEN + 2] = { 0 };
    int result_index = 0, result_len;
    order_changes = 0;


    for (int i = 0; i < second_len; i++)
    {
        //printf("i = %d, second_num = %c, order_changes = %d\n", i, second_num[i], order_changes);
        multiplicate_line_and_symbol(first_num, second_num[i], buf);
        //output_intermediate_result(result);

        my_plus_copy(result_index, buf, result);
        //output_intermediate_result(result);
        result_index += 1;
        result_len = strlen(result);

        if (result_len == MAX_MANTISSA_LEN + 1)
        {
            move_digits(result);
            result_index--;
            order_changes++;
        }
        //output_intermediate_result(result);
    }
    //printf("order_changes = %d\n", order_changes);

    my_plus_copy(0, result, result_num);
}

void multiply_sign(char s1, char s2, char *s3)
{
    if (s1 == s2)
        *s3 = '+';
    else
        *s3 = '-';
}

void delete_zeros(char mantissa[MAX_MANTISSA_LEN + 1], int *order)
{
    int len = strlen(mantissa), new_len = len;
    int k = 0;
    int i = len - 1;
    while (i > 0)
    {
        //printf("mantissa[i] = %c, mantissa[index_rewrite_num] = %c, index_rewrite_num = %d\n", mantissa[i], mantissa[index_rewrite_num], index_rewrite_num);
        if (mantissa[i] == '0' && k == 0)
        {
            new_len -= 1;
        }
        i--;
    }
    mantissa[new_len] = 0;
    (*order) += len - new_len;
}

int multiplicate(fns first_num, sns second_num, fns *answer)
{
    int order_changes = 0;
    multiplicate_two_strings(first_num.mantissa, second_num.num, answer->mantissa, order_changes);
    //printf("order_start = %ld, order_result = %d\n", first_num.order, order_changes);
    //printf("answer_order = %ld", answer->order);
    //output_intermediate_result(answer->mantissa);
    delete_zeros(answer->mantissa, &order_changes);
    //output_intermediate_result(answer->mantissa);
    answer->order = first_num.order + order_changes;
    multiply_sign(first_num.sign, second_num.sign, (&(answer->sign)));
    return 0;
}
