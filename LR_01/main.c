#include "common.h"
#include "input_output.h"
#include "multiplication.h"

int main()
{
    fns first_num = {{0}, 0, 0};
    sns second_num = {{0}, 0};
    fns answer_num = {{0}, 0, 0};
    output_start_first_num_message();
    int rc = read_first_number(&first_num);
    if (rc != INOUT_OK)
    {
        output_error_message(rc);
        return rc;
    }
    output_start_second_num_message();
    rc = read_second_number(&second_num);
    if (rc != INOUT_OK)
    {
        output_error_message(rc);
        return rc;
    }
    multiplicate(first_num, second_num, &answer_num);
    //printf("--------ENDING CALCULATING--------\n");
    //output_first_number(first_num);
    //output_second_num(second_num);
    rc = output_first_number(answer_num);

    if (rc != INOUT_OK)
    {
        output_error_message(rc);
        return rc;
    }
    return rc;
}
