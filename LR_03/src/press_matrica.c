#include "../inc/press_matrica.h"

int press_create_matrix(press_matrix *m, int a_size, int ia_size, int ja_size)
{
    int rc;
    rc = create_vector(&(m->a), a_size);
    if (rc != OK)
    {
        return rc;
    }
    rc = create_vector(&(m->ia), ia_size);
    if (rc != OK)
    {
        return rc;
    }
    rc = create_list_el(&(m->ja_head));
    if (rc != OK)
    {
        return rc;
    }

    list_el *new_el;
    for (int i = 0; i < ja_size - 1; i++)
    {
        create_list_el(&new_el);
        m->ja_head = new_elem_add_end(m->ja_head, new_el);
    }

    m->a.size = a_size;
    m->ia.size = ia_size;
    return OK;
}

void press_free_matrica(press_matrix *p)
{
    free_vector(&(p->a));
    free_vector(&(p->ia));
    free_list(p->ja_head);
}

int press_find_count_elems(norm_matrix m)
{
    int elem = 0, count = 0;
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            norm_get_element_from_matrix_by_i_j(m, i, j, &elem);
            if (elem != 0)
            {
                count++;
            }
        }
    }
    return count;
}

int press_norm_matrica_to_press(norm_matrix nm, press_matrix *pm)
{
    int elem_count, rc, elem = 0, column_el_count = 0;
    int *point_a, *point_ia;
    list_el *cur_el_ja;

    elem_count = press_find_count_elems(nm);

    rc = press_create_matrix(pm, elem_count, elem_count, nm.columns + 1);
    //press_output_matrica(*pm);
    if (rc != OK)
    {
        return rc;
    }
    point_a = (pm->a.elements);
    point_ia = (pm->ia.elements);
    cur_el_ja = (pm->ja_head);


    elem_count = 1;
    cur_el_ja->value = elem_count;
    cur_el_ja = cur_el_ja->next;
    for (int i = 0; i < nm.columns; i++)
    {
        for (int j = 0; j < nm.rows; j++)
        {
            norm_get_element_from_matrix_by_i_j(nm, j, i, &elem);
            if (elem != 0)
            {
                *point_a = elem;
                point_a++;
                *point_ia = j;
                point_ia++;
                elem_count++;
                column_el_count++;
            }
        }
        if (column_el_count == 0 && i != nm.columns - 1)
        {
            cur_el_ja->value = 0;
        }
        else
        {
            cur_el_ja->value = elem_count;
        }
        cur_el_ja = cur_el_ja->next;
        column_el_count = 0;
    }
    return OK;
}

void press_output_matrica(press_matrix m)
{
    printf("%2s - ", "A");
    for (int i = 0; i < m.a.size; i++)
    {
        printf("%2d ", *(m.a.elements + i));
    }
    printf("\n");

    printf("%2s - ", "IA");
    for (int i = 0; i < m.ia.size; i++)
    {
        printf("%2d ", *(m.ia.elements + i));
    }
    printf("\n");

    printf("%2s - ", "JA");
    for (list_el *i = m.ja_head; i; i = i->next)
    {
        printf("%2d ", i->value);
    }
    printf("\n");
}

int get_column_size(list_el *element)
{
    int size = -1, cur_el = element->value;
    while (size == -1)
    {
        element = element->next;
        if (element == NULL)
            break;
        if (element->value == 0)
            continue;
        size = element->value - cur_el;
        //printf("cur_el = %d, size = %d\n", cur_el, size);
    }
    return size;
}

int see_i_element_at_list(list_el *head, int index)
{
    for (int i = 0; i < index; i++, head = head->next);
    return head->value;
}

int get_column_count(list_el *head)
{
    int size = 0;
    for (list_el *column = head; column; column = column->next)
    {
        size += 1;
    }
    return size - 1;
}

int get_row_count(press_matrix pm)
{
    int cur_column_index = 0, row = 0, max_row = 0, size = 0;
    for (list_el *column = pm.ja_head; column->next; column = column->next, cur_column_index++)
    {
        if (column->value == 0)
            continue;
        size = get_column_size(column) + 1;
        //printf("column_size = %d\n", size);
        for (int i = 0; i < size; i++)
        {
            row = *(pm.ia.elements + i + cur_column_index);
            //printf("row = %d\n, i = %d, cur_column_index = %d *(pm.ia.elements + i + cur_column_index) = %d\n", row, i, cur_column_index, *(pm.ia.elements + i + cur_column_index));
            if (row > max_row)
            {
                max_row = row;
            }
        }
    }

    //printf("max_row = %d\n", max_row);
    return max_row + 1;
}

int press_check_matrica(press_matrix a, press_matrix b)
{
    int a_columns = 0, b_rows = 0;
    a_columns = get_column_count(a.ja_head);
    b_rows = get_row_count(b);
    //printf("a_columns = %d, b_rows = %d\n", a_columns, b_rows);

    if (a_columns < b_rows)
    {
        return ERROR_DIFFERENT_MATRIX;
    }
    return OK;
}

int press_multiplicate_vector_to_matrica(press_matrix vector, press_matrix matrica,
                                          press_matrix *result)
{
    int size, rc = 0;
    int first_multiplier, second_multiplier = 0;
    int cur_index_matrica, cur_index_vector, result_index = 0;

    rc = press_check_matrica(vector, matrica);
    if (rc != OK)
    {
        return ERROR_DIFFERENT_MATRIX;
    }

    list_el *current_result_ja = result->ja_head;

    for (list_el *column = matrica.ja_head; column->next; column = column->next)
    {
        current_result_ja->value = result_index + 1;
        current_result_ja = current_result_ja->next;
        size = get_column_size(column);
        for (int i = 0; i < size; i++)
        {
            first_multiplier = *(matrica.a.elements + (column->value - 1 + i));

            cur_index_matrica = *(matrica.ia.elements + (column->value - 1 + i));
            cur_index_vector = see_i_element_at_list(vector.ja_head, cur_index_matrica);
            if (cur_index_vector == 0)
                continue;
            second_multiplier = *(vector.a.elements + cur_index_vector - 1);

            *(result->a.elements + result_index) = first_multiplier * second_multiplier;
            *(result->ia.elements + result_index) = *(matrica.ia.elements + i + column->value - 1);

            result_index++;
        }
    }
    current_result_ja->value = result_index + 1;
    current_result_ja->next = NULL;
    return OK;
}

void press_matrica_output_as_normal(press_matrix pm)
{
    int size = 0, cur_column_index = 0, row = 0, cur_row_index = 0;
    int columns_count = get_column_count(pm.ja_head);
    int rows_count = get_row_count(pm);
    int rc = 0;
    norm_matrix nm;
    rc = norm_create_matrica(&nm, rows_count, columns_count);
    if (rc != OK)
        return;

    for (list_el *column = pm.ja_head; column->next; column = column->next, cur_column_index++)
    {
        size = get_column_size(column);
        for (int i = 0; i < size; i++)
        {
            row = *(pm.ia.elements + cur_row_index);
            *(nm.elements + row*columns_count + cur_column_index) = *(pm.a.elements +
                                                                     cur_row_index);
            cur_row_index++;
        }
    }
    norm_output_matrica(nm);
}
