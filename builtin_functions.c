#include "shell.h";
/**
 * cd - function to change the current working directory
 * @line: command line string
 * 
*/
void cd(char *line)
{
    int i, tokens_count = 0;
	char **tokens_array;
	const char *delim = "\n\t ";

	tokens_array = get_tokens(line, delim, tokens_count);
	if (tokens_array[0] == NULL)
	{
		free_single_pointer(2, tokens_array, line);
		return;
	}
	if (tokens_array[1] == NULL)
	{
		i = get_path("HOME");
		chdir((environ[i]) + 5);
	}
	else if (_strcmp(tokens_array[1], "-") == 0)
		print_str(tokens_array[1], 1);

	else
		chdir(tokens_array[1]);
	free_double_pointer(tokens_array);
    
}

/**
 * env - function that prints all the environmental variables.
 * @line: command line string
 */
void env(__attribute__((unused))char *line)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(1, &environ[i][j], 1);
		write(1, "\n", 1);
	}
}

/**
 * exit - Exits the shell. After freeing allocated resources.
 * @line: command line string
 */
void exit(char *line)
{
	free(line);
	print_str("\n", 0);
	exit(1);
}


/**
 * get_builtin - checks for builtin functions in array
 * @command: command array passed to the shell
 * @line: command line string
 * Return: if found function 0 else -1
 */
int get_builtin(char **command, char *line)
{
	int i;
	void (*build)(char *);
	builtin_t buildin[] = {
		{"cd", cd},
		{"env", env},
		{"exit", exit},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].type != NULL; i++)
	{
		if (_strcmp(command[0], buildin[i].type) == 0)
		{
			build  = buildin[i].func;
			break;
		}
	}
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", command[0]) == 0)
		free_double_pointer(command);
	build(line);
	return (0);
}