#include "../inc/testing.h"

int test_norm_matrix_time(norm_matrix m1, norm_matrix m2)
{
    norm_matrix nm3;
    norm_create_matrica(&nm3, m1.rows, m2.columns);
    int start, end;
    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        norm_multiplicate_matrica_and_matrica(m1, m2, &nm3);
    }
    end = clock();
    norm_free_matrica(&nm3);
    return end - start;
}

int test_press_matrix_time(press_matrix m1, press_matrix m2)
{
    //printf("succes start\n");
    press_matrix pm3;
    int len_ja;
    len_ja = get_column_count(m2.ja_head);

    //printf("succes get columns\n");
    press_create_matrix(&pm3, m2.a.size, m2.a.size, len_ja + 1);
    int start, end;
    //printf("succes create\n");
    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        press_multiplicate_vector_to_matrica(m1, m2, &pm3);
    }
    //printf("succes multiplication test\n");
    end = clock();
    //free_vector(&(pm3.a));
    //free_vector(&(pm3.ia));
    //free_list(pm3.ja_head);
    //press_free_matrica(&pm3);
    //printf("succes free\n");
    return end - start;
}
/*
void output_testing_result(norm_matrix nm1, norm_matrix nm2, press_matrix pm1,
                           press_matrix pm2)
{
    int time_press = 0, time_norm = 0;
    int size_press, size_norm;
    size_press = sizeof(press_matrix);
    size_norm = sizeof(norm_matrix);
    time_norm = test_norm_matrix(nm1, nm2);
    time_press = test_press_matrix(pm1, pm2);

    printf("Умножение обычных матриц A*B заняло по времени %d мсек, по памяти %d байт",
           time_norm, size_norm);
    printf("Умножение разреженных вектора  и матрицы заняло по времени %d мсек, по памяти %d байт",
           time_press, size_press);
}
*/
void make_norm_matrix_zero(norm_matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            norm_put_element_from_matrix_by_i_j(m, i, j, 0);
        }
    }
}

void big_testing()
{
    norm_matrix nm1, nm2;
    press_matrix pm1, pm2;
    int size_press, size_norm, time_press, time_norm;
    int rc;

    printf("Таблица с результатами тестирования\n");
    printf("|%15s|%15s|%6s|%8s|%8s|\n", "matrix type", "fill percent", "size", "time",
           "memory");

    for (int i = 1; i < 11; i++)
    {
        if (i == 4 || i == 6 || i == 7 || i == 8 || i == 9)
            continue;

        rc = norm_create_matrica(&nm1, i*10, i*10);
        if (rc != OK)
        {
            output_error_message(rc);
            return;
        }
        rc = norm_create_matrica(&nm2, i*10, i*10);
        if (rc != OK)
        {
            output_error_message(rc);
            return;
        }

        for (int j = 0; j < 11; j++)
        {
            if (j == 4 || j == 6 || j == 7 || j == 8 || j == 9)
                continue;
            

            make_norm_matrix_zero(&nm1);
            make_norm_matrix_zero(&nm2);
            //printf("good start\n");
            norm_make_rand_matrica(&nm1, j*10);
            //printf("good create 1\n");
            norm_make_rand_matrica(&nm2, j*10);
            //printf("good create 2\n");
            rc = press_norm_matrica_to_press(nm1, &pm1);
            if (rc != OK)
            {
                output_error_message(rc);
                return;
            }
            rc = press_norm_matrica_to_press(nm2, &pm2);
            if (rc != OK)
            {
                output_error_message(rc);
                return;
            }

            size_norm = (nm1.rows * nm1.columns * sizeof(int) + sizeof(norm_matrix)) * 3;
            size_press = (nm1.rows * nm1.columns * j * 10 * sizeof(int) +
                          nm1.columns * sizeof(int) + sizeof(norm_matrix)) * 3;
            //printf("good size\n");

            time_norm = test_norm_matrix_time(nm1, nm2);
            //printf("good time 1\n");
            time_press = test_press_matrix_time(pm1, pm2);
            //printf("good time 2\n");
            printf("|%15s|%15d|%6d|%8d|%8d|\n", "norm", j*10, i*10, time_norm, size_norm);
            printf("|%15s|%15d|%6d|%8d|%8d|\n", "press", j*10, i*10, time_press, size_press);

            press_free_matrica(&pm1);
            press_free_matrica(&pm2);
            //printf("J = %d\n", j);
        }
        //printf("end\n");
        norm_free_matrica(&nm1);
        //printf("end\n");
        norm_free_matrica(&nm2);
        //printf("end\n");
    }
    //printf("end\n");
}
