#include "shell.h"
/**
 * _strlen - Count lenght of the poniter
 * @s: pointer
 * Return: lenght
*/
int _strlen(char *s)
{
	int i;
	int len;

	for (i = 0; s[i] != '\0'; i++)
		len++;
	return (len);
}
/**
 * get_flags - get flags to command
 * @argv: direction pointer
 * @string: Pointer to string
 * @bytes_read: size of string
 * Return: None
 */
void get_flags(char **argv, char *string, ssize_t bytes_read)
{
	char **arguments = argv;
	int i = 0, j = 0;
	char *token = strtok(string, " ");

	while (token != NULL)
	{
		arguments[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	arguments[i] = NULL;
	arguments[i - 1] = strtok(arguments[i - 1], NEW_LINE);
}
/**
* _strchr - a function that locates a character in a string
* @s: pointer that locate a character.
* Return: pointer.
*/
int _strchr(char *s)
{
	if (s[0] == 47)
		return (0);
	else
		return (-1);
}
