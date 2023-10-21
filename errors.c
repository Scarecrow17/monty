#include "monty.h"

/**
 * err - Print  error messages by error code.
 * @error_code: error code below
 * (1) => no file
 * (2) => file cant open
 * (3) => wrong instruction
 * (4) => cant malloc
 * (5) => non int
 * (6) => empty for pint
 * (7) => empty for pop
 * (8) => short stack
 */
void err(int error_code, ...)
{
	va_list ag;
	char *oq;
	int num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 1:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			fprintf(stderr, "Error: Can't open file %s\n",
				va_arg(ag, char *));
			break;
		case 3:
			num = va_arg(ag, int);
			oq = va_arg(ag, char *);
			fprintf(stderr, "L%d: unknown instruction %s\n", num, oq);
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(ag, int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * more_err - handles errors.
 * @error_code: error codes below
 * (6) => empty pint
 * (7) => empty pop
 * (8) => short stack
 * (9) => undefined
 */
void more_err(int error_code, ...)
{
	va_list ag;
	char *oq;
	int num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 6:
			fprintf(stderr, "L%d: can't pint, stack empty\n",
				va_arg(ag, int));
			break;
		case 7:
			fprintf(stderr, "L%d: can't pop an empty stack\n",
				va_arg(ag, int));
			break;
		case 8:
			num = va_arg(ag, unsigned int);
			oq = va_arg(ag, char *);
			fprintf(stderr, "L%d: can't %s, stack too short\n", num, oq);
			break;
		case 9:
			fprintf(stderr, "L%d: division by zero\n",
				va_arg(ag, unsigned int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * string_err - handles errors
 * @error_code: error codes below
 * (10) ~> out of ASCII
 * (11) ~> empty stack
 */
void string_err(int error_code, ...)
{
	va_list ag;
	int num;

	va_start(ag, error_code);
	num = va_arg(ag, int);
	switch (error_code)
	{
		case 10:
			fprintf(stderr, "L%d: can't pchar, value out of range\n", num);
			break;
		case 11:
			fprintf(stderr, "L%d: can't pchar, stack empty\n", num);
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
