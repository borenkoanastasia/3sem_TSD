#include "choises.h"

void output_work_normal_matrixes(norm_matrix a, norm_matrix b)
{
    printf("Матрица A");
    norm_output_matrica(a);
    printf("\n");
    printf("Матрица B");
    norm_output_matrica(b);
    printf("\n");


    int rc = norm_check_matrica(a, b);
    if (rc != OK)
    {
        printf("Предупреждение: Эти матрицы нельзя перемножить. Длина строки матрицы А %s\n",
               "должна совпадать с длиной столбца матрицы B");
    }
}

void output_work_press_matrixes(press_matrix a, press_matrix b)
{
    printf("Вектор A");
    press_output_matrica(a);
    printf("\n");
    printf("Матрица B");
    press_output_matrica(b);
    printf("\n");


    int rc = press_check_matrica(a, b);
    if (rc != OK)
    {
        printf("Предупреждение: Эти матрицы нельзя перемножить. Длина строки вектора А %s\n",
               "должна совпадать с длиной столбца матрицы B");
    }
}

int input_manually_or_random()
{
    int rc = 0, con = 0;
    char space[] = "   ";
    printf("Введите пункт из списка, чтобы выбрать тип ввода.");
    printf("%s1.Ввод вручную", space);
    printf("%s2.Автозаполнение случайными числами", space);
    rc = scanf("%d", &con);
    if (con == 1)
        return MANNUALY;
    if (con == 2)
        return RANDOM;
    return GO_AWAY;
}

int input_press_matrica_elements_columns(int *elem_count, int *columns)
{
   int rc = 0;
   printf("Введите кол-во ненулевых элементов: ");
   rc = scanf("%d", elem_count);
   if (rc != 1)
   {
       return ERROR_INPUT;
   }
   printf("Введите кол-во столбцов: ");
   rc = scanf("%d", columns);
   if (rc != 1)
   {
       return ERROR_INPUT;
   }
   return OK;
}

int input_press_matrica_ja(press_matrix *m, int columns, int elem_count)
{
    printf("%2s :", "A");
    output_vector(m->a);
    printf("%2s :", "IA");
    output_vector(m->ia);
    printf("Введите индексы элементов в а и ia, с которых начинается описание нового %s%d%s):\n",
           "столбца (введено должно быть ", columns + 1, "элементов");

    int rc = 0;
    list_el *pointer = m->ja_head;

    for (int i = 0; i < columns; i++)
    {
        printf("Введите индекс для %d столбца: ", i);
        rc = scanf("%d", &(pointer->value));
        if (rc != 1)
        {
            return ERROR_INPUT;
        }
        pointer = pointer->next;
    }
    pointer->value = elem_count;
    return OK;
}

int input_press_matrica_a_ia(press_matrix *m, int elem_counts, int vector_condition)
{
    printf("Введите все ненулевые элементы матрицы (чтение элементов идет по столбцам, %s).\n",
           "сначала все элементы 1-ого столбца, потом 2-ого и т.д.");
    if (!vector_condition)
    {
        printf("После каждого элемента введите индекс его строки.\n");
    }
    int rc = 0;

    for (int i = 0; i < elem_counts; i++)
    {
        printf("Введите %d ненулевой элемент: ", i + 1);
        rc = scanf("%d", (m->a.elements + i));
        if (rc != 1)
        {
            return ERROR_INPUT;
        }
        if (!vector_condition)
        {
            printf("Введите индекс строки этого элемента: ");
            rc = scanf("%d", (m->ia.elements + i));
            if (rc != 1)
            {
                return ERROR_INPUT;
            }
        }
        else
        {
            *(m->ia.elements + i) = 0;
        }
    }
    return OK;
}

void input_press_matrica_manually(press_matrix *m, int vector_condition)
{
    press_matrix m1;
    int elem_count, columns, rc = 0;
    rc = input_press_matrica_elements_columns(&elem_count, &columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    rc = press_create_matrix(&m1, elem_count, elem_count, columns+1);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    rc = input_press_matrica_a_ia(&m1, elem_count, vector_condition);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    rc = input_press_matrica_ja(&m1, columns, elem_count);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    *m = m1;
}

int input_norm_matrica_size(int *rows, int *columns)
{
    int rc = 0;
    printf("Введите кол-во строк матрицы: ");
    rc = scanf("%d", rows);
    if (rc != 1)
    {
        return ERROR_INPUT;
    }
    printf("Введите кол-во столбцов матрицы: ");
    rc = scanf("%d", columns);if (rc != 1)
    {
        return ERROR_INPUT;
    }
    return OK;
}

int input_norm_vector_size(int *columns)
{
    int rc = 0;
    printf("Введите длину вектора: ");
    rc = scanf("%d", columns);
    if (rc != 1)
    {
        return ERROR_INPUT;
    }
    return OK;
}

int input_norm_matrica_elements(norm_matrix *m)
{
    int rc = 0, elem = 0;
    printf("Введите элементы матрицы: \n");
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            printf("Введите %2d %2d элемент матрицы: ", i, j);
            rc = scanf("%d", &elem);
            if (rc != 1)
            {
                return ERROR_INPUT;
            }
            norm_put_element_from_matrix_by_i_j(m, i, j, elem);
        }
    }
    return OK;
}

void input_norm_matrica_manually(norm_matrix *m)
{
    int rows, columns, rc;
    norm_matrix m1;
    rc = input_norm_matrica_size(&rows, &columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    rc = norm_create_matrica(&m1, rows, columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    rc = input_norm_matrica_elements(&m1);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    *m = m1;
}

int input_procent(int *procent)
{
    int rc = 0;
    printf("Введите процент заполнения матрицы");
    rc = scanf("%d", procent);
    if (rc != 1)
    {
        return ERROR_INPUT;
    }
    return OK;
}

void input_press_matrica_random(press_matrix *m, int vector_condition)
{
    norm_matrix m1;
    int rows, columns, rc = 0, procent;
    if (vector_condition)
    {
        rc = input_norm_vector_size(&columns);
        rows = 1;
        if (rc != OK)
        {
            output_error_message(rc);
            return;
        }
    }
    else
    {
        rc = input_norm_matrica_size(&rows, &columns);
        if (rc != OK)
        {
            output_error_message(rc);
            return;
        }
    }
    rc = norm_create_matrica(&m1, rows, columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    rc = input_procent(&procent);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    norm_make_rand_matrica(&m1, procent);
    press_norm_matrica_to_press(m1, m);
}

void input_norm_matrica_random(norm_matrix *m)
{
    norm_matrix m1;
    int rows, columns, rc = 0, procent;
    rc = input_norm_matrica_size(&rows, &columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }

    rc = norm_create_matrica(&m1, rows, columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    rc = input_procent(&procent);
    if (rc != OK)
    {
        output_error_message(rc);
        return;
    }
    norm_make_rand_matrica(&m1, procent);
    *m = m1;
}
