#include "shell.h"

/**
 * free_mal - free malloc
 * @argv: direction pointer
 * Return: None
 */
void free_mal(char **argv)
{
	char **aux = argv;

	free(aux);
}
/**
 * create_mal - free malloc
 * @argv: direction pointer
 * Return: None
 */
char **create_mal(size_t size)
{
	char **argv;

	argv = malloc(sizeof(char *) * size);
	if (!argv)
		exit(0);
	return (argv);
}
