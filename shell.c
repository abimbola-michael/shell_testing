#include "shell.h"

/**
 * main - program entry point
 * @argc: arg count
 * @argv: arg vector
 * Return: Always 0.
 */

int main(__attribute__((unused)) int argc, char **argv)
{
	char *line;
	int commands_count;
	size_t size;

	commands_count = 0;
	signal(SIGINT, SIG_IGN);
	do {
		commands_count++;
		line = NULL;
		size = 0;
		parse_line(line, size, commands_count, argv);

	} while (1);

	return (0);
}
