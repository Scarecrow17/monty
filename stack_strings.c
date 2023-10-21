#include "monty.h"

/**
 * print_char - Prints thlue.
 * @stack: Pointerstack.
 * @line_number: Interger re opcode.
 */
void print_char(stack_t **stack, unsigned int line_number)
{
	int asci;

	if (stack == NULL || *stack == NULL)
		string_err(11, line_number);

	asci = (*stack)->n;
	if (asci < 0 || asci > 127)
		string_err(10, line_number);
	printf("%c\n", asci);
}

/**
 * print_str - Printstring.
 * @stack: Pointer tthe stack.
 * @ln: Interger r opcode.
 */
void print_str(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	int asci;
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}

	tmp = *stack;
	while (tmp != NULL)
	{
		asci = tmp->n;
		if (asci <= 0 || asci > 127)
			break;
		printf("%c", asci);
		tmp = tmp->next;
	}
	printf("\n");
}

/**
 * rotl - Rotates the firsck to the bottom.
 * @stack: Pointer ack.
 * @ln: Interger  opcode.
 */
void rotl(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	(*stack)->prev = tmp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}


/**
 * rotr - Rotates the last the top.
 * @stack: Pointe stack.
 * @ln: Interger re the opcode.
 */
void rotr(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	(*stack)->prev = tmp;
	(*stack) = tmp;
}
