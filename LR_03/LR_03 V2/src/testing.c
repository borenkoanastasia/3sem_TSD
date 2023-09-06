#include "../inc/testing.h"

int test_norm_matrix_time(norm_matrix_t m1, norm_matrix_t m2)
{
    norm_matrix_t nm3;
    int rc;

    rc = create_norm_matrix(&nm3, m1.rows, m2.columns);
    if(rc != OK)
        return -1;

    int start, end;
    start = clock();

    for (int i = 0; i < 100; i++)
    {
        norm_multiply_vec_and_matrica(m1, m2, &nm3);
    }

    end = clock();

    free_norm_matrix(&nm3);
    return end - start;
}

int test_press_matrix_time(press_matrix_t m1, press_matrix_t m2)
{
    press_matrix_t pm3;

    create_press_matrix(&pm3, m2.a.size, m2.ja.size);
    //printf("good start\n");
    int start, end;

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        pm_miltiply_row_and_matrix(m1, m2, &pm3);
        //printf("good *\n");
    }
    end = clock();
    //printf("good multiplicate\n");

    free_press_matrix(&pm3);
    //printf("good free\n");

    return end - start;
}
/*
void make_norm_matrix_zero(norm_matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            norm_put_element_from_matrix_by_i_j(m, i, j, 0);
        }
    }
}*/

void big_testing()
{
    norm_matrix_t nm1, nm2;
    press_matrix_t pm1, pm2;
    int size_press, size_norm, time_press, time_norm;
    int rc;

    printf("Таблица с результатами тестирования\n");
    printf("|%15s|%15s|%6s|%8s|%8s|\n", "matrix type", "fill percent", "size", "time",
           "memory");

    for (int i = 1; i < 11; i++)
    {
        //if (i == 4 || i == 6 || i == 7 || i == 8 || i == 9)
        //    continue;

        rc = create_norm_matrix(&nm1, 1, i*10);
        if (rc != OK)
        {
            output_error_message(rc);
            return;
        }
        rc = create_norm_matrix(&nm2, i*10, i*10);
        if (rc != OK)
        {
            output_error_message(rc);
            return;
        }

        for (int j = 0; j < 11; j++)
        {
            //if (j == 4 || j == 6 || j == 7 || j == 8 || j == 9)
            //    continue;
            

            nm_make_matrix_zero(&nm1);
            nm_make_matrix_zero(&nm2);
            //printf("good start\n");
            norm_make_rand_matrica(&nm1, j*10);
            //printf("good create 1\n");
            norm_make_rand_matrica(&nm2, j*10);
            //printf("good create 2\n");
            rc = pm_press_nm_to_pm(nm1, &pm1);
            if (rc != OK)
            {
                output_error_message(rc);
                return;
            }
            rc = pm_press_nm_to_pm(nm2, &pm2);
            if (rc != OK)
            {
                output_error_message(rc);
                return;
            }

            size_norm = (nm1.rows * nm1.columns * sizeof(int) + sizeof(norm_matrix_t)) * 3;
            size_press = (nm1.rows * nm1.columns * j * 10 * sizeof(int) +
                          nm1.columns * sizeof(int) + sizeof(norm_matrix_t)) * 3;
            //printf("good size\n");

            time_norm = test_norm_matrix_time(nm1, nm2);
            //printf("good time 1\n");
            time_press = test_press_matrix_time(pm1, pm2);
            //printf("good time 2\n");
            printf("|%15s|%15d|%6d|%8d|%8d|\n", "norm", j*10, i*10, time_norm, size_norm);
            printf("|%15s|%15d|%6d|%8d|%8d|\n", "press", j*10, i*10, time_press, size_press);

            free_press_matrix(&pm1);
            free_press_matrix(&pm2);
            //printf("J = %d\n", j);
        }
        //printf("end\n");
        free_norm_matrix(&nm1);
        //printf("end\n");
        free_norm_matrix(&nm2);
        //printf("end\n");
    }
    //printf("end\n");
}
