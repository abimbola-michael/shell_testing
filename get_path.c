#include "shell.h";

/**
 * get_command_path - get the directory of command and merges with command
 * @command: input command
 * Return: full command path
 */
char *get_command_path(char *command)
{
	char *str = "PATH";
	char **path_tokens;
    char *full_path;
	int path_index;
	char *directory;
    char *env_variable;
	int token_count = 0;
    int len;
	const char *delim = ":\n";
	char **path_tokens;

	path_index = search_path(str);
    len = _strlen(str);
	env_variable = environ[path_index] + (len + 1);
	path_tokens = get_tokens(env_variable, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);

	directory = search_directories(path_tokens, command);
	if (directory == NULL)
	{
		free_double_pointer(path_tokens);
		return (NULL);
	}

	full_path = build_path(directory, command);
	if (full_path == NULL)
	{
		free_double_pointer(path_tokens);
		return (NULL);
	}

	free_double_pointer(path_tokens);

	return (full_path);
}
/**
 * search_path - finds index of an environmental variable.
 * @str: input string
 * Return: if successful returns the right environmental variable index
 */
int search_path(char *str)
{
	int i;
	int len;
	int j;

	len = _strlen(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}

/**
 * search_directories - searches directories of a command path for command
 * @path_tokens: array of string path
 * @command: input command
 * Return: directory found if not null
 */

char *search_directories(char **path_tokens, char *command)
{
	int i, s;
	char *cwd;
	char *buffer = NULL;
	size_t size = 0;
	struct stat stat_buffer;

	cwd = getcwd(buffer, size);
	if (cwd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (i = 0; path_tokens[i] != NULL; i++)
	{
		s = chdir(path_tokens[i]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(command, &stat_buffer);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[i]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}

/**
 * build_path - combines the command path and command together
 * @directory: input directory
 * @command: input command
 * Return: full command path if success else NULL
 */
char *build_path(char *directory, char *command)
{
	int i, j;
    int len;
	char *full_path;

	if (directory == NULL || command == NULL)
		return (NULL);
	len = _strlen(directory) + _strlen(command) + 2;

	full_path = malloc(sizeof(char) * len);
	if (full_path == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		for (j = 0; directory[j] != '\0'; j++, i++)
			full_path[i] = directory[j];
		full_path[i] = '/';
		i++;
		for (j = 0; command[j] != '\0'; j++, i++)
			full_path[i] = command[j];
	}
	full_path[--i] = '\0';
	return (full_path);
}
