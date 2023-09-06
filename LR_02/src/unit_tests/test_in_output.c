#include "../inc/menu.h"

int main()
{
    countries example[41] = {{{0}, 0 , {0}, {0}, {0}, {{0}}}};
    output_start_message();
    output_table(example, 41);
    output_menu_message();
}
