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
void _salir(char **argv, char *value, char *string)
{
    int n;
    int *cpy;

    free(value);
    free(string);
    if (argv[1] == NULL)
        free_mal(argv), exit(0);
    else
    {
        cpy = malloc(sizeof(int));
        *cpy = _atoi(argv[1]);
        n = *cpy;
        free_mal(argv);
        free(cpy);
        exit(n);
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