#include "shell.h"

/**
 * main - basic shell
 * @argc: unused.
 * @av: name of file.
 * @environ: variables.
 * Return: prints in screen $ and received commands
 */
int main(__attribute__((unused)) int argc, char *av[], char **environ)
{
	char **argv;
	size_t size = 0;
	ssize_t bytes_read = 0;
	char *string = NULL, *aux = NULL;
	int com_count = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			if (write(0, "$ ", 2) < 0)
				exit(0);
		}
		bytes_read = getline(&string, &size, stdin);
		com_count++;
		if (bytes_read == EOF)
			free(string), exit(0);
		aux = string;
		while (*aux != '\0')
		{
			if (*aux != ' ' && *aux != '\t')
			{
				break;
			}
			aux++;
		}
		if (*aux == '\n' || *aux == ' ' || *aux == '\t')
			continue;
		argv = create_mal(size);
		if (_strchr(aux) == 0)
			exec_dir(argv, aux, environ, av, com_count, 1);
		else
			exec_path(argv, aux, environ, av, com_count);
		free_mal(argv);
	}
	return (0);
}
