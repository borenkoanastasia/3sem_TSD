#include "../inc/read_file.h"
#include "../inc/output_graph.h"
#include "../inc/delete_peak.h"
#include "../inc/connectivity.h"
#include <time.h>

int one_test(graph_t *g)
{	
	graph_t *g2;
	int connectivity, calculation;
	array_t *ans_arr;
	int k = 0;
	int start, end;
	
	ans_arr = create_array(g->peaks->len);
	start = clock();
	for (int i = 0; i < g->peaks->len; i++)
	{
		copy_graphs(*g, &g2);
		delete_peak(g2, i + 1);
		connectivity = check_graph_connectivity(*g2);
		calculation = check_calculation(*g2);
		if (connectivity == TRUE && calculation == TRUE)
		{
			ans_arr->elements[k] = i + 1;
			k++;
			//printf("true\n");
		}
		//else
			//printf("false\n");
		//printf("%d\n", i);
		tw_delete_graph(g2);
	}

	end = clock();
	return end - start;
}

int testing(graph_t *g)
{
	int sum = 0;
	int count_repeat = COUNT_REPEAT;

	for (int i = 0; i < count_repeat; i++)
	{
		sum += one_test(g);
	}
	return sum/count_repeat;
}

int main()
{
	graph_t *g, *g2;
	char filename[21];
	int rc, connectivity, calculation;
	
	printf("Введите название файла (не более 20 символов)\n");
	rc = scanf("%20s", filename);
	if (rc != 1)
		return ERR_INPUT;
	
	rc = read_file(filename, &g);
	if (rc != OK)
	{
		printf("Нет такого файла или в файле допущена ошибка. Код ошибки:%d\n", rc);
		//tw_output_graph(*g);
		return 0;
	}

	connectivity = check_graph_connectivity(*g);
	calculation = check_calculation(*g);
	if (connectivity == TRUE && calculation == TRUE)
	{
		printf("Граф уже дерево\n");
		return 0;
		//printf("true\n");
	}

	array_t *ans_arr;
	ans_arr = create_array(g->peaks->len);
	int k = 0;
	char cur_file[20];
	for (int i = 0; i < g->peaks->len; i++)
	{
		copy_graphs(*g, &g2);
		delete_peak(g2, i + 1);
		connectivity = check_graph_connectivity(*g2);
		calculation = check_calculation(*g2);
		if (connectivity == TRUE && calculation == TRUE)
		{
			ans_arr->elements[k] = i + 1;
			k++;
			//printf("true\n");
		}
		//else
			//printf("false\n");
		//printf("%d\n", i);
		tw_delete_graph(g2);
	}
	printf("Среднее время, затраченное на обработку: %d (Взято среднее арифметическое за %d повторов)\n", testing(g), COUNT_REPEAT);
	if (ans_arr->elements[0] != 0)
	{
		printf("И заданного графа можно сделать дерево удалением одной из следущих вершин: ");
		output_array(*ans_arr);
		output_graph_as_dot(*g, "main_graph.dot");
		int i = 0;
		while (ans_arr->elements[i] != 0)
		{
			snprintf(cur_file, 20, "%d_graph.dot", i + 1);
			copy_graphs(*g, &g2);
			delete_peak(g2, ans_arr->elements[i]);
			//tw_output_graph(*g2);
			//printf("%s\n", cur_file);
			output_graph_as_dot(*g2, cur_file);
			tw_delete_graph(g2);
			i++;
		}
	}
	else
	{
		printf("И заданного графа нельзя сделать дерево удалением одной из вершин.\n");
		output_graph_as_dot(*g, "main_graph.dot");
	}
	int sum = 0;
	for (int i = 0; i < ans_arr->len; i++)
	{
		if (ans_arr->elements[i] == 0)
			break;
		sum++;
	}
	delete_array(ans_arr);
	//tw_output_graph(*g2);
	//output_graph_as_dot(*g2);

	tw_delete_graph(g);
	//tw_delete_graph(g2);
	return sum;
}