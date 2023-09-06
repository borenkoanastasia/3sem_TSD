#include "../inc/input.h"

int input_manually_or_random()
{
    int rc = 0, con = 0;
    char space[] = "   ", str_buf[20];
    printf("Введите пункт из списка, чтобы выбрать тип ввода.\n");
    printf("%s1.Ввод вручную\n", space);
    printf("%s2.Автозаполнение случайными числами\n", space);
    rc = scanf("%d", &con);
    if (rc != 1)
    {
        scanf("%s", str_buf);
        return GO_AWAY;
    }
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
    int rc;

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

int input_press_matrica_manually(press_matrix *m, int vector_condition)
{
    press_matrix m1;
    int elem_count, columns, rc = 0;
    rc = input_press_matrica_elements_columns(&elem_count, &columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    rc = press_create_matrix(&m1, elem_count, elem_count, columns+1);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    rc = input_press_matrica_a_ia(&m1, elem_count, vector_condition);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    rc = input_press_matrica_ja(&m1, columns, elem_count);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    *m = m1;
    return OK;
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

int input_norm_matrica_manually(norm_matrix *m)
{
    int rows, columns, rc;
    norm_matrix m1;
    rc = input_norm_matrica_size(&rows, &columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    rc = norm_create_matrica(&m1, rows, columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    rc = input_norm_matrica_elements(&m1);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    *m = m1;
    return OK;
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

int input_press_matrica_random(press_matrix *m, int vector_condition)
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
            return GO_AWAY;
        }
    }
    else
    {
        rc = input_norm_matrica_size(&rows, &columns);
        if (rc != OK)
        {
            output_error_message(rc);
            return GO_AWAY;
        }
    }
    rc = norm_create_matrica(&m1, rows, columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    rc = input_procent(&procent);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    norm_make_rand_matrica(&m1, procent);
    press_norm_matrica_to_press(m1, m);
    return OK;
}

int input_norm_matrica_random(norm_matrix *m)
{
    norm_matrix m1;
    int rows, columns, rc = 0, procent;
    rc = input_norm_matrica_size(&rows, &columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }

    rc = norm_create_matrica(&m1, rows, columns);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    rc = input_procent(&procent);
    if (rc != OK)
    {
        output_error_message(rc);
        return GO_AWAY;
    }
    norm_make_rand_matrica(&m1, procent);

    *m = m1;
    return OK;
}

int input_two_norm_matrixes(norm_matrix *m1, norm_matrix *m2)
{
    int rc;
    rc = input_manually_or_random();
    if (rc == MANNUALY)
    {
        rc = input_norm_matrica_manually(m1);
        if (rc != OK)
            return rc;
        rc = input_norm_matrica_manually(m2);
        return rc;
    }
    else if (rc == RANDOM)
    {
        rc = input_norm_matrica_random(m1);
        if (rc != OK)
            return rc;
        rc = input_norm_matrica_random(m2);
        return rc;
    }
    return rc;
}

int input_press_vector_and_matrix(press_matrix *m1, press_matrix *m2)
{
    int rc;
    rc = input_manually_or_random();
    if (rc == MANNUALY)
    {
        rc = input_press_matrica_manually(m1, 1);
        if (rc != OK)
            return rc;
        rc = input_press_matrica_manually(m2, 0);
        return rc;
    }
    else if (rc == RANDOM) 
    {
        rc = input_press_matrica_random(m1, 1);
        if (rc != OK)
            return rc;
        rc = input_press_matrica_random(m2, 0);
        return rc;
    }
    return rc;
}