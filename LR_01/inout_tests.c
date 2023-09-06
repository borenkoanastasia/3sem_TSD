#include "input_output.h"
/*
int output_digits(fns first_num)
{
    printf("DIGITS (len = %d):   ", first_num.mantissa_len);
    for (int i = 0; i < first_num.mantissa_len; i++)
    {
        printf("%d ", first_num.mantissa[i]);
    }
    printf("    ORDER    ");
    printf("%ld", first_num.order);

    //printf("     rc = %d      ", rc);
    return 0;
}*/

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

int main()
{
    //int digits[MAX_MANTISSA_LEN + 2], len, order;
    fns first_num = {{0}, 0, 0};
    sns second_num = {{0}, 0};
    printf("START READING\n");
    int rc = read_first_number(&first_num);
    rc = read_second_number(&second_num);
    printf("END REDING (rc = %d)\n", rc);
    printf("START OUTPUT\n");
    output_first_number(first_num);
    output_second_num(second_num);
    printf("END OUTPUT\n");
    return 0;
}
