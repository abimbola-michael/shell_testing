#include "shell.h"

/**
 * print_char - prints a char
 * @c: line char
 * Return: number of chars
 */

int print_char(char c)
{
	return (write(1, &c, 1));
}

/**
 * print_str - prints a string.
 * @str: line string
 * @plus_new_line: if 1 print new line otherwise just the string
 */

void print_str(char *str, int plus_new_line)
{
	int i;

	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i]; i++)
		write(1, &str[i], 1);
	if (plus_new_line == 1)
		write(1, "\n", 1);
}

/**
 * print_num - prints an unsigned number
 * @n: line int
 * Return: size of number printed
 */

int print_num(int n)
{
	int len = 0, divisor = 1;
	unsigned int num;

	num = n;

	while (num / divisor > 9)
		divisor *= 10;

	while (divisor != 0)
	{
		len += print_char('0' + num / divisor);
		num %= divisor;
		divisor /= 10;
	}

	return (len);
}

/**
 * print_error - prints error message when command is not found.
 * @arg: name of the shell program.
 * @count: commands count
 * @command: line command
 */

void print_error(char *arg, int count, char *command)
{
	print_str(arg, 0);
	print_str(": ", 0);
	print_num(count);
	print_str(": ", 0);
	print_str(command, 0);
}

/**
 * print_exec_error - prints execve error messages.
 * @arg: name of the shell program.
 * @count: commands count
 * @command: line command
 */

void print_exec_error(char *arg, int count, char *command)
{
	print_error(arg, count, command);
	print_str(": ", 0);
	perror("");
	exit(1);
}
