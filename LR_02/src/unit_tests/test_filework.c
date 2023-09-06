#include "../inc/file.h"
#include "../inc/menu.h"

int main()
{
    char filename[] = "table_file.txt";
    int len = 0, rc = 0;
    countries arr[MAX_STRUCT_COUNT];
    rc = read_file_to_struct(filename, arr, &len);
    printf("len = %d\n", len);
    if (rc != FILEWORK_OK)
    {
        printf("ERROR\n");
        printf("rc = %d\n", rc);
        filework_output_error_messages(rc);
    }
    output_table(arr, len);
    return 0;
}
