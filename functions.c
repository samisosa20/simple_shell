#include "shell.h"
/**
 * _strlen - Count lenght of the poniter
 * @s: pointer
 * Return: lenght
*/
int _strlen(char *s)
{
	int i = 0;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}
/**
 * get_flags - get flags to command
 * @argv: direction pointer
 * @string: Pointer to string
 * Return: None
 */
void get_flags(char **argv, char *string)
{
	char **arguments = argv;
	int i = 0;
	char delimit[] = " \t";
	char *token = strtok(string, delimit);

	if (_strcmp(token, "/bin/echo") == 0 || _strcmp(token, "echo") == 0)
	{
		while (token != NULL)
		{
			arguments[i] = token;
			if (i == 0)
				token = strtok(NULL, " ");
			else
			{
				if (*token == '\"')
					token = strtok(NULL, "\"");
				else
					token = strtok(NULL, " ");
			}
			i++;
		}
	}
	else
	{
		while (token != NULL)
		{
			
			arguments[i] = token;
			token = strtok(NULL, delimit);
			i++;
		}
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
/**
* _strcat - appends the src string to the dest string.
* @dest: pointer to appens src.
* @src: appends to dest.
* Return: pointer.
*/
char *_strcat(char *dest, char *src)
{
	int dest_len = _strlen(dest);
	int i;

	for (i = 0 ; src[i] != '\0' ; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
/**
* *_strcpy - function that copies the string pointed to by src,
* including the terminating null byte (\0), to the buffer pointed to by dest.
* @dest: pointer to paste
* @src: pointer to copy
* Return: pointer.
*/
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	while (src[x] != '\0')
	{
		dest[x] = src[x];
		x++;
	}

	dest[x] = '\0';
	return (dest);
}
