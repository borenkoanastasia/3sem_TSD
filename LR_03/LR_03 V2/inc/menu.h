#ifndef MENU_H
#define MENU_H

#include "input.h"
#include "norm_matrix.h"
#include "press_matrix.h"
#include "testing.h"
#include "common.h"
#include "create.h"

#define MAX_CHOISE_NAME 200
#define MAX_CHOISE_AMOUNT 3

#define CHOISE_EXIT 0
#define CHOISE_NOT_EXIT 1

typedef struct choise choise;

struct choise
{
	char name[MAX_CHOISE_NAME];
	void (*action) (void);
};

int make_main_choises(choise choises_arr[MAX_CHOISE_NAME]);

void menu(choise choises_arr[MAX_CHOISE_NAME], int len);

#endif // MENU_H