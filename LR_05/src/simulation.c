
// Моделирование процесса
int model()
{
	turn_t oa1_turn, oa2_turn;
	oa1->len = 0;
	oa2->len = 0;
	rc = fill_turn(oa1);
	if (rc != OK)
		return rc;

	float res_time = 0;     // Общее (снхронизированное) время - наименьшее из возможных
	float dif_time = 0;     // Разница времени знак соответствует знаку разности oa2_time - oa1_time 
	float downtime_oa2 = 0; // Время простоя автомата 2

	float cur_time_oa1 = 0;
	float cur_time_oa2 = 0;

	int cond_oa1_empty = 0;
	int cond_oa2_empty = 0;	
	int oa1_tasks = 0;      // Кол-во вызовов автомата ОА1
	int oa2_tasks = 0;      // Кол-во вызовов автомата ОА2

	average_t oa1_average_len, oa2_average_len = 0;

	
	while (oa2_tasks != MAX_OA2_TASKS)
	{
		if (fabs(cur_time_oa1) < EPS and oa1->pout != NULL)
		{
			cur_time_oa1 = beat_oa1(&oa1, &oa2);
			oa1_tasks += 1;
		}
		if (fabs(cur_time_oa2) < EPS and oa2->pout != NULL)
		{
			cur_time_oa2 = beat_oa2(&oa1, &oa2);
			oa2_tasks += 1;
		}

		if (oa2->pout == NULL)
		{
			res_time += cur_time_oa1;
			downtime_oa2 += cur_time_oa1;
			cur_time_oa1 = 0;
			cur_time_oa2 = 0; 
		}
		else if (oa1->pout == NULL)
		{
			res_time += cur_time_oa2;
			downtime_oa2 += cur_time_oa2;
			cur_time_oa1 = 0;
			cur_time_oa2 = 0; 
		}
		else if ((cur_time_oa2 - cur_time_oa1) < EPS)
		{
			res_time += cur_time_oa1;
			cur_time_oa1 = 0;
			cur_time_oa2 = 0; 
		}
		else if (cur_time_oa2 < cur_time_oa1)
		{
			res_time += cur_time_oa2;
			cur_time_oa1 = cur_time_oa1 - cur_time_oa2;
		}
		else if ((cur_time_oa2 > cur_time_oa1))
		{
			res_time += cur_time_oa1;
			cur_time_oa2 = cur_time_oa2 - cur_time_oa1;
		}
		oa1_average_len->sum += oa1.len;
		oa2_average_len->sum += oa2.len;
		oa1_average_len->el_count += 1;
		oa2_average_len->el_count += 1;
	}
	return res_time;
}