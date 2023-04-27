#include "shell.h";

/**
 * parse_command_line - Parses the command line
 * @line: line string.
 * @size: size and initially 0.
 * @commands_count: commands count
 * @argv: name of command line
 */
void parse_command_line(char *line, size_t size, int commands_count, char **argv)
{
	int i;
    char *cmd_prompt = "($) ";
	ssize_t read_len;
	int tokens_count = 0;
	char **tokens_array;
	const char *delim = "\n\t ";

	write(1, cmd_prompt, _strlen(cmd_prompt));
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		tokens_array = get_tokens(line, delim, tokens_count);
		if (tokens_array[0] == NULL)
		{
			free_single_pointer(2, tokens_array, line);
			return;
		}
		i = get_builtin(tokens_array, line);
		if (i == -1)
			create_fork(tokens_array, line, tokens_count, argv);
		for (i = 0; tokens_array[i] != NULL; i++)
			free(tokens_array[i]);
		free_single_pointer(2, tokens_array, line);
	}
	else
		exit_b(line);
}

/**
 * create_fork - Creates a fork to able able to execute another program
 * @tokens_array: array of pointers to string tokens
 * @line: The contents of the read line.
 * @commands_count: commands count
 * @argv: name of command line
 */
void create_fork(char **tokens_array, char *line, int commands_count, char **argv)
{
	pid_t id;
    int i;
	int status;
	int check;
	struct stat buffer;
	char *command;
	char *command_template;

	id = fork();
	if (id == 0)
	{
		command_template = tokens_array[0];
		command = get_command_path(tokens_array[0]);
		if (command == NULL)
		{
			check = stat(tokens_array, &buffer);
			if (check == -1)
			{
				print_error(argv[0], commands_count, command_template);
				print_str(": not found", 1);
				free_single_pointer(2, line, command_template);
				for (i = 1; tokens_array[i]; i++)
					free(tokens_array[i]);
				free(tokens_array);
				exit(100);
			}
			command = command_template;
		}
		tokens_array[0] = command;
		if (tokens_array[0] != NULL)
		{
			if (execve(tokens_array[0], tokens_array, environ) == -1)
				print_exec_error(argv[0], commands_count, command_template);
		}
	}
	else
		wait(&status);
}