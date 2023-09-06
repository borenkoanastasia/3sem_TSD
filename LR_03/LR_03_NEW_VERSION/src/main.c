#include "../inc/menu.h"

int main()
{
	choise choises_arr[MAX_CHOISE_AMOUNT];
	int len = make_main_choises(choises_arr);
	menu(choises_arr, len);
	return 0;
}