#include "shell.h"

/**
 * count_tokens - counts arguments passed to the shell.
 * @line: String that is separated by an specified delimeter
 * @delim:  delimeter used to separate the tokens.
 * Return: total args count or -1 if fails.
 */

int count_tokens(char *line, const char *delim)
{
	char *str;
	char *token;
	int i;

	str = _strdup(line);
	if (str == NULL)
		return (-1);
	token = strtok(str, delim);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delim);
	free(str);
	return (i);
}

/**
 * get_tokens - used to get the tokens from the line
 * @line: line string
 * @delim: delimeter used to separate the tokens.
 * @token_count: tokens count
 * Return: array of tokens if success else null
 */

char **get_tokens(char *line, const char *delim, int token_count)
{
	int i;
	char **line_array;
	char *token;
	char *line_cpy;

	token_count = count_tokens(line, delim);
	if (token_count == -1)
	{
		free(line);
		return (NULL);
	}
	line_array = malloc(sizeof(char *) * (token_count + 1));
	if (line_array == NULL)
	{
		free(line);
		return (NULL);
	}
	line_cpy = _strdup(line);
	token = strtok(line_cpy, delim);
	for (i = 0; token != NULL; i++)
	{
		line_array[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	line_array[i] = NULL;
	free(line_cpy);

	return (line_array);
}
