#include "shell.h"
/**
* _strcmp - function that compares two strings.
* @s1: string nro 1.
* @s2: string nro 2.
* Return: comparate.
*/
int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}

/**
* *_salir - exit function
* @argv: Pointer to free
* @string: pointer to free
* @status_exit: status_exit
* Return: pointer.
*/
int _salir(char **argv, char *string, int status_exit)
{
	int n;

	if (_strcmp(argv[0], "exit") == 0)
	{
		if (argv[1] == NULL)
		{
			free_mal(argv), free(string);
			exit(status_exit);
		}
		else
		{
			n = _atoi(argv[1]);
			free_mal(argv), free(string);
			exit(n);
		}
	}
	else
	{
		free_mal(argv);
		free(string);
		return (status_exit);
	}
}
/**
* *_atoi - print only number
* @s: pointer to extrac number
* Return: pointer.
*/
int _atoi(char *s)
{
	int aux, i, sig;

	sig = 1;
	i = aux = 0;
	while ((s[i] < '0' || s[i] > '9') && s[i] != 0)
	{
		if (s[i] == '-')
			sig = sig * -1;
		i++;
	}
	while ((s[i] >= '0' && s[i] <= '9') && s[i] != 0)
	{
		if (aux >= 0)
		{
			aux = aux * 10 - (s[i] - '0');
			i++;
		}
		else
		{
			aux = aux * 10 - (s[i] - '0');
			i++;
		}
	}
	sig = sig * -1;
	return (aux * sig);
}
/**
* *error_ex - show error
* @string: show argument and length
* @av: name of the program
* @com_count: line run
* Return: pointer.
*/
void error_ex(char *string, char *av[], int com_count)
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
	if (write(2, "not found\n", 10) < 0)
		exit(127);
}
/**
 * print_error - print errors
 * @argv: arguments pointer
 * @av: main arguments pointer
 * @com_count: integer number of commands
 * Return: dir path
*/
void print_error(char **argv, char *av[], int com_count)
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
	if (write(2, argv[0], _strlen(argv[0])) < 0)
		exit(127);
	if (write(2, ": ", 2) < 0)
		exit(127);
}
