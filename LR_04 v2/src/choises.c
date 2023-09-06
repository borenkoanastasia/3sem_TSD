#include "../inc/choises.h"

void choise_list_stacks_sort(adress_stack_node_t **h)
{
	list_stack_node_t *head1 = NULL, *head2 = NULL, *head3 = NULL;
	int rc;
	//printf("Good start\n");
	rc = input_list_stack(&head1);
	//printf("rc = %d\n", rc);
	if (rc != OK)
		return;
	//printf("Good input 1\n");
	rc = input_list_stack(&head2);
	if (rc != OK)
		return;
	//printf("Good input 2\n");

	list_output_stack(head1);
	list_output_stack(head2);
	
	list_sort(&head1, &head2, &head3, h);
	
	list_output_stack(head1);
	list_output_stack(head2);
	list_output_stack(head3);
}

void choise_array_stacks_sort(adress_stack_node_t **h)
{
	array_stack_t stack1, stack2, stack3;
	int rc;
	rc = input_array_stack(&stack1);
	if (rc != OK)
		return;
	rc = input_array_stack(&stack2);
	if (rc != OK)
		return;
	array_create_stack(&stack3, (stack1.aub - stack1.alb) *2);

	array_output_stack(stack1);
	array_output_stack(stack2);
	
	array_sort(&stack1, &stack2, &stack3, h);
	
	array_output_stack(stack1);
	array_output_stack(stack2);
	array_output_stack(stack3);

	array_stack_free(&stack1);
	array_stack_free(&stack2);
	array_stack_free(&stack3);
}

void choise_output_adress_stack(adress_stack_node_t **h)
{
	output_free_adresses(*h);
}
