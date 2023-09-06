#include "../inc/experiment.h"

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
		output_final_result(t1, t2, a1, a2, sys_time, array_get_average_time);
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
	list_turn_t *t1, *t2;
	automat_t a1, a2;
	my_time_t sys_time;
	list_prepearing_turns(&t1, &t2);
	list_prepearing_automats(&a1, &a2, &t1, &t2);
	sys_time = list_modeling(&t1, &t2, &a1, &a2, condition);
	if (condition == SHOW)
	{
		output_final_result(t1, t2, a1, a2, sys_time, list_get_average_time);
	}
	list_delete_turn(&t1);
	list_delete_turn(&t2);
	delete_node(&(a1.next_turns->next));
	delete_node(&(a1.next_turns));
} 