#include "shell.h"

/**
 * free_mal - free malloc
 * @argv: direction pointer
 * Return: None
 */
void free_mal(char **argv)
{
	char **aux = argv;
	int i;

	for (i = 0; aux[i]; i++)
		free(aux[i]);
	free(aux);
}
/**
 * create_mal - free malloc
 * @argv: direction pointer
 * Return: None
 */
char **create_mal(void)
{
	int i;
	char **argv;

	argv = malloc(sizeof(char *));
	if (!argv)
		exit(0);
	for (i = 0; argv[i]; i++)
	{
		argv[i] = malloc(sizeof(char *));
		if (!argv[i])
			free(argv), exit(0);
	}
	return (argv);
}
