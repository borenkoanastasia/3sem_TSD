#include "../inc/experiment.h"

int input_choide_output(int *choise)
{
	printf("Выводить список очищенных ячеек памяти?\n");
	printf("\t1. Да\n");
	printf("\t2. Нет\n");
	int rc = scanf("%d", choise);
	if (rc != 1)
	{
		clearInputBuf();
		return ERR_INPUT;
	}
	return OK;
}

void array_experiment(int condition)
{
	array_turn_t *t1, *t2;
	automat_t a1, a2;
	my_time_t sys_time;
	array_prepearing_turns(&t1, &t2);
	array_prearing_automats(&a1, &a2, &t1, &t2);
	//array_output_turn(*t1);
	//array_output_turn(*t2);
	sys_time = array_modeling(&t1, &t2, &a1, &a2, condition);
	if (condition == SHOW)
	{
		output_line(50);
		output_final_result(t1, t2, a1, a2, sys_time, array_get_average_time);
		output_line(50);
	}
	array_delete_turn(&t1);
	array_delete_turn(&t2);
	/*if (a1.current_request != NULL)
	{
		//delete_request((a1.current_request->element));
		//delete_node(&(a1.current_request));
	}*/
	delete_node(&(a1.next_turns->next));
	delete_node(&(a1.next_turns));
}
void list_experiment(int condition)
{
	adress_stack_node_t *adress_stack = NULL;
	list_turn_t *t1, *t2;
	automat_t a1, a2;
	my_time_t sys_time;
	int choise = 0;


	list_prepearing_turns(&t1, &t2);
	list_prepearing_automats(&a1, &a2, &t1, &t2);
	sys_time = list_modeling(&t1, &t2, &a1, &a2, &adress_stack, condition);
	if (condition == SHOW)
	{
		output_line(50);
		output_final_result(t1, t2, a1, a2, sys_time, list_get_average_time);
		output_line(50);
		input_choide_output(&choise);
		if (choise == 1)
			output_adresses(adress_stack);
	}
	list_delete_turn(&t1);
	list_delete_turn(&t2);
	delete_node(&(a1.next_turns->next));
	delete_node(&(a1.next_turns));

	free_adresses(&adress_stack);
} 

void time_list_experiment(int condition)
{
	list_turn_t *t1, *t2;
	automat_t a1, a2;
	my_time_t sys_time;


	list_prepearing_turns(&t1, &t2);
	list_prepearing_automats(&a1, &a2, &t1, &t2);
	sys_time = time_list_modeling(&t1, &t2, &a1, &a2, condition);
	if (condition == SHOW)
	{
		output_line(50);
		output_final_result(t1, t2, a1, a2, sys_time, list_get_average_time);
		output_line(50);
	}
	list_delete_turn(&t1);
	list_delete_turn(&t2);
	delete_node(&(a1.next_turns->next));
	delete_node(&(a1.next_turns));

} 
