#include "monty.h"
/**
 *push - adds values on top of the stack
 *@stack:pointer to the stack doubly linked list
 *@line_number: line number of monty file to parse
 *Return:void
 */
void push(stack_t **stack, unsigned int line_number)
{
	int number, i = 0;
	char *n = mon.args[1];

	if (n == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_number);
		freer();
		exit(EXIT_FAILURE);
	}
	/*check if the string contains an integer*/
	while (n[i])
	{
		if ((is_no(n[i]) == 0 && n[i] != '-') || (n[i] == '-' && n[i + 1] == '\0'))
		{
			dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_number);
			freer();
			exit(EXIT_FAILURE);
		}
		i++;
	}
	number = atoi(n);
	mon.args[1] = NULL;
	if (mon.stack_queue == 1)
		add_dnodeint_end(stack, number);
	else
		add_node_beg(stack, number);
}
/**
 *pall - prints all the values of the stack from the top
 *@stack:pointer to the stack
 *@ln:line number
 *Return:void
 */
void pall(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;

	(void)ln;
	if (tmp == NULL)
		return;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (tmp->prev != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->prev;
	}
	printf("%d\n", tmp->n);
}
/**
 *pint - prints the top value of a stack
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void pint(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;

	if (tmp == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pint, stack empty\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	printf("%d\n", tmp->n);
}
/**
 *pop - removes the top element of a stack
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void pop(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;

	if (tmp == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pop an empty stack\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->prev)
	{
		tmp->prev->next = NULL;
	}
	free(tmp);
	if (tmp->prev == NULL)
		*stack = NULL;
}
/**
 *swap - swaps the two topmost elements of a stack
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void swap(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int swap_n;

	if (tmp == NULL || tmp->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't swap, stack too short\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	swap_n = tmp->prev->n;
	tmp->prev->n = tmp->n;
	tmp->n = swap_n;
}
/**
 *add - adds the two topmost elements of a stack
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void add(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int sum;

	if (tmp == NULL || tmp->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	sum = tmp->n + tmp->prev->n;
	tmp->prev->n = sum;
	tmp->prev->next = NULL;
	free(tmp);
}
/**
 *nop - doesn't do anything
 *@stack:pointer to stack
 *@ln:line number
 *Return: void
 */
void nop(stack_t **stack, unsigned int ln)
{
	(void)stack;
	(void)ln;
}
/**
 *sub - subtracts the topmost element from the second topmost
 *element
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void sub(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int sub_n;

	if (tmp == NULL || tmp->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't sub, stack too short\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	sub_n = tmp->prev->n - tmp->n;
	tmp->prev->n = sub_n;
	tmp->prev->next = NULL;
	free(tmp);
}
/**
 *div_op - divides the second top element by the top element in the stack
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void div_op(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int div_n;

	if (tmp == NULL || tmp->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't div, stack too short\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->n == 0)
	{
		dprintf(STDERR_FILENO, "L%d: division by zero\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	div_n = tmp->prev->n / tmp->n;
	tmp->prev->n = div_n;
	tmp->prev->next = NULL;
	free(tmp);
}
/**
 *mul - multiplies the second top element of a stack with the top
 *element
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void mul(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int mul_n;

	if (tmp == NULL || tmp->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't mul, stack too short\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	mul_n = tmp->prev->n * tmp->n;
	tmp->prev->n = mul_n;
	tmp->prev->next = NULL;
	free(tmp);
}
#include "monty.h"
/**
 *mod - computes the remainder of the division of the second topmost
 *element by the topmost element
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void mod(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int mod_n;

	if (tmp == NULL || tmp->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->n == 0)
	{
		dprintf(STDERR_FILENO, "L%d: division by zero\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	mod_n = tmp->prev->n % tmp->n;
	tmp->prev->n = mod_n;
	tmp->prev->next = NULL;
	free(tmp);
}
/**
 *pchar - prints the char at the top followed by a newline
 *Description:top value is treated as ASCII of the top char
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void pchar(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;

	if (tmp == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pchar, stack empty\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->n < 0 || tmp->n > 127)
	{
		dprintf(STDERR_FILENO, "L%d: can't pchar, value out of range\n", ln);
		freer();
		exit(EXIT_FAILURE);
	}
	printf("%c\n", tmp->n);
}
/**
 *pstr - prints ascii of stack elements from top
 *@stack:pointer to stack
 *@ln:line number
 * Return:void
 */
void pstr(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;

	(void)ln;
	if (tmp == NULL)
	{
		printf("\n");
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (tmp && tmp->n != 0 && (tmp->n > 0 && tmp->n <= 127))
	{
		printf("%c", tmp->n);
		tmp = tmp->prev;
	}
	printf("\n");
}
/**
* rotl - function that rotates a stack by one to the top.
* @stack: first parameter
*@ln: second parameter
*
* Return: void
*/
void rotl(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int rotl_n;

	(void)ln;
	if (tmp == NULL)
		return;
	while (tmp->next != NULL)
		tmp = tmp->next;
	rotl_n = tmp->n;
	while (tmp->prev != NULL)
	{
		tmp->n = tmp->prev->n;
		tmp = tmp->prev;
	}
	tmp->n = rotl_n;
}

/**
  * rotr - opcode that rotates a stack to the bottom
  * @stack: 1st paramenter
  * @ln: 2nd parameter
  *
  * Return: void
  */
void rotr(stack_t **stack, unsigned int ln)
{
	stack_t *tmp = *stack;
	int rotr_n;

	(void)ln;
	if (tmp == NULL)
		return;
	rotr_n = tmp->n;
	while (tmp->next != NULL)
	{
		tmp->n = tmp->next->n;
		tmp = tmp->next;
	}
	tmp->n = rotr_n;
}
/**
 *stack - changes stack_queue int to 1 so that a stack is implemente
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void stack(stack_t **stack, unsigned int ln)
{
	(void)ln;
	(void)stack;

	mon.stack_queue = 1;
}
/**
 *queue - changes stack_queue int to 0 so that we push to a queue
 *@stack:pointer to stack
 *@ln:line number
 *Return:void
 */
void queue(stack_t **stack, unsigned int ln)
{
	(void)stack;
	(void)ln;

	mon.stack_queue = 0;
}
