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
	char **argv, *dir_path;
	size_t size = 0;
	ssize_t bytes_read = 0;
	char *string = NULL, *aux = NULL;
	int com_count = 0;

	dir_path = _get_path(environ);
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
		if (*aux == '\n' || *aux == ' ' || *aux == '\t' || *aux == '.')
			continue;
		argv = create_mal(size);
		get_flags(argv, aux);
		argv[0] = _strchr_echo(argv[0], '\"');
		aux = _strchr_echo(aux, '\"');
		if (_strchr(aux) == 0)
			exec_dir(argv, aux, environ, av, com_count, 1);
		else
			exec_path(argv, aux, environ, av, com_count, dir_path);
		free_mal(argv);
	}
	return (0);
}
