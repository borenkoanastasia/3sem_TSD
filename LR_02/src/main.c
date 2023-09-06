#include "../inc/common.h"
#include "../inc/file.h"
#include "../inc/help_functions.h"
#include "../inc/check_fields.h"
#include "../inc/key_array.h"
#include "../inc/menu.h"
#include "../inc/struct_array.h"
#include "../inc/testing.h"

int main()
{
    char filename[] = "table_file.txt";
    countries arr[MAX_STRUCT_COUNT];
    int len = 0;
    int rc = 0;

    rc = read_file_to_struct(filename, arr, &len);
    //printf("%d\n", len);
    if (rc != FILEWORK_OK)
    {
        //filework_output_error_messages(rc);
        printf("При считывании файла произошла ошибка. \n%s",
               "Проверьте наличие файла в директории и правильность его заполнения.\n");
        return ERROR_FILE;
    }
    output_start_message();
//    output_table(arr, len);

    int condition = 1;
    int choice = 0;

    while (condition)
    {
        //printf("len = %d\n", len);
        output_menu_message();
        rc = scanf("%d", &choice);
        fgetc(stdin);
        if (rc == 1)
        {
            rc = make_choise(choice, arr, &len, filename);
            if (rc == 1)
                condition = 0;
        }
        else
            condition = 0;
    }
    //struct_array_quick_sort(arr, 0, len);
    //sort(arr, len);
    //output_table(arr, len);
    return OK;
}
