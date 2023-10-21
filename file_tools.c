#include "monty.h"

/**
 * open_file - open file
 * @file_name: file name
 * Return: none
 */

void open_file(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		err(2, file_name);

	read_file(fd);
	fclose(fd);
}


/**
 * read_file - read file
 * @fd: point to file descriptor
 * Return: none
 */

void read_file(FILE *fd)
{
	int line_num, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_num = 1; getline(&buffer, &len, fd) != -1; line_num++)
	{
		format = parse_line(buffer, line_num, format);
	}
	free(buffer);
}


/**
 * parse_line - Separates line to tokens
 * @buffer: line from file
 * @line_number: line num
 * @format:  storage format. 
 * Return: 0 if stack. 1 queue.
 */

int parse_line(char *buffer, int line_number, int format)
{
	char *opc, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		err(4);

	opc = strtok(buffer, delim);
	if (opc == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opc, "stack") == 0)
		return (0);
	if (strcmp(opc, "queue") == 0)
		return (1);

	find_func(opc, value, line_number, format);
	return (format);
}

/**
 * find_func - find function for the opcode
 * @opcode: opcode
 * @value: argument opcode
 * @format:  storage format. 
 * @ln: line number
 * Return: void
 */
void find_func(char *opcode, char *value, int ln, int format)
{
	int p;
	int flg;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flg = 1, p = 0; func_list[p].opcode != NULL; p++)
	{
		if (strcmp(opcode, func_list[p].opcode) == 0)
		{
			call_fun(func_list[p].f, opcode, value, ln, format);
			flg = 0;
		}
	}
	if (flg == 1)
		err(3, ln, opcode);
}


/**
 * call_fun - Call required function.
 * @func: Point function that is called.
 * @op: string opcode.
 * @val: string numeric value.
 * @ln: line num for instruction.
 * @format: Format specifier. 
 */
void call_fun(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flg;
	int p;

	flg = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flg = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (p = 0; val[p] != '\0'; p++)
		{
			if (isdigit(val[p]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flg);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
