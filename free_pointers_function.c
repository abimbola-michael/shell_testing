#include "shell.h"

/**
 * free_single_pointer - frees a single pointer.
 * @n: number of pointers to free.
 */

void free_single_pointer(int n, ...)
{
	int i;
	char *str;
	va_list p_list;

	va_start(p_list, n);
	for (i = 0; i < n; i++)
	{
		str = va_arg(p_list, char*);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(p_list);
}

/**
 * free_double_pointer - frees double pointer.
 * @pointer: line pointer
 */

void free_double_pointer(char **pointer)
{
	int i;

	for (i = 0; pointer[i] != NULL; i++)
		free(pointer[i]);
	free(pointer);
}


