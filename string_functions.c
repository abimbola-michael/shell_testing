#include "shell.h";

/**
 * _strlen - calculates the length of a string.
 * @str: line string.
 * Return: string length or 0 if null.
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i])
    {
        i++;
    }
		
	return (i);
}
/**
 * _strdup - duplicates a string
 * @src: line string
 * Return: copy of string
 */
char *_strdup(char *src)
{
	int i, len;
	char *dest;

	len = _strlen(src);
	dest = malloc(sizeof(char) * (len + 1));

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - compares two strings for match
 * @s1: first line string
 * @s2: second line string
 * Return: 0 if match and -1 if not.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	if (_strlen(s1) != _strlen(s2))
		return (-1);
	for (i = 0; s1[i]; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}