#include "shell.h"

/**
 * rev_string - isdigit
 * @s: integer
 * Return: prints alphabet
*/
void rev_string(char *s)
{
	int i = 0;
	int len = 0;
	char save = 0;
	int final = 0;

	for (i = 0; s[i] != '\0'; i++)
		len++;
	final = len - 1;

	for (i = final; i >= (final - i); i--)
	{
		save = s[(final - i)];
		s[(final - i)] = s[i];
		s[i] = save;
	}
}
/**
* _itos - change int to string
 * @num: number to conver
 * @string: pointer
 * @cont: counter
 * @sign: signal
 * Return: None
*/
void _itos(long int num, char *string, int cont, int sign)
{
	if (num == 0)
	{
		if (sign == -1)
		{
			string[0] = '-';
			string[1] = '\0';
		}
		else
			string[0] = '\0';
		rev_string(string - cont);
	}
	else
	{
		string[0] = (num % 10) + '0';
		num /= 10;
		_itos(num, string + 1, cont + 1, sign);
	}
}

/**
* _get_path - a function that gets the path
* @environ: pointer that locate a character.
* Return: pointer.
*/
char *_get_path(char **environ)
{
	int w, x;
	char strpath[] = "PATH=";
	char buffer[1024], *extra = buffer;

	for (w = 0; environ[w]; w++)
	{
		for (x = 0; environ[w][x] && x < 5; x++)
		{
			if (environ[w][x] != strpath[x])
				break;
			if (x == 4)
				extra = environ[w];
		}
	}
	while (*extra != '\0')
	{
		if (*extra == '=')
		{
			extra++;
			break;
		}
		extra++;
	}
	return (extra);
}

/**
* detect_slash - detects an slash or an space on the shell
* @c: the slash or space
* @string: the string that the user enter
* Return: an int
*/

int detect_slash(char c, char *string)
{
	int i = 0;

	while (string[i])
	{
	if (string[i] != c && string[i] != ' ')
		return (0);
	i++;
	}
	return (1);
}

/**
* *error_perm - show error
* @string: show argument and length
* @av: name of the program
* @com_count: line run
* Return: pointer.
*/

void error_perm(char *string, char *av[], int com_count)
{
	char com_num[1024];

	_itos(com_count, com_num, 0, 1);
	if (write(2, av[0], _strlen(av[0])) < 0)
		exit(127);
	if (write(2, ": ", 2) < 0)
		exit(127);
	if (write(2, com_num, _strlen(com_num)) < 0)
		exit(127);
	if (write(2, ": ", 2) < 0)
		exit(127);
	if (write(2, string, _strlen(string)) < 0)
		exit(127);
	if (write(2, ": ", 2) < 0)
		exit(127);
	if (write(2, "Permission denied\n", 19) < 0)
		exit(127);
}
