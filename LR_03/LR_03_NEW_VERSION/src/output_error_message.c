#include "../inc/common.h"

void output_error_message(int rc)
{
    switch(rc)
    {
    case OK:
        break;
    case ERROR_DIFFERENT_MATRIX:
        printf("Умножение невозможно, т.к. длина строки матрицы A не равна длине столбца %s\n",
               "матрицы B");
        break;
    case ERROR_INPUT:
        printf("Некорректный ввод\n");
        break;
    case ERROR_CREATE:
        printf("Не удалось выделить память под матрицу\n");
        break;
    case ERROR_INDEX_NOT_IN_MATRIX:
        printf("Индекс выходит за пределы матрицы\n");
        break;
    case ERROR_INDEX_NOT_IN_VECTOR:
        printf("Индекс выходит за пределы вектора\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
    }
}
