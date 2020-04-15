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
	char *string;
	int com_count = 0;

	dir_path = _get_path(environ);
	while (1)
	{
		string = NULL;
		if (isatty(STDIN_FILENO) == 1)
			if (write(0, "$ ", 2) < 0)
				exit(0);
		bytes_read = getline(&string, &size, stdin);
		com_count++;
		if (bytes_read == EOF)
			free(string), exit(0);
		while (*string != '\0')
		{
			if (*string != ' ' && *string != '\t')
				break;
			string++;
		}
		if (validate_com(string) == -1)
			continue;
		argv = create_mal(size);
		get_flags(argv, string);
		argv[0] = _strchr_echo(argv[0], '\"');
		string = _strchr_echo(string, '\"');
		if (detect_slash('/', string) == 1 || (string[0] == '.' && string[1] == '.' &&
			 string[2] == '\0'))
			error_perm(string, av, com_count);
		else
		{
			if (_strchr(string) == 0)
				verify_dir(argv, string, environ, av, com_count, 1);
			else
				exec_path(argv, string, environ, av, com_count, dir_path); }
		free_mal(argv);
		if (!*string)
			free(string);
	}
	return (0); }

int validate_com(char *aux)
{
	if (*aux == '\n' || *aux == ' ' || *aux == '\t' ||
		(*aux == '.' && aux[1] == '\n'))
		return(-1);
	return(0);
}

char *_clean_line(char *aux)
{
	int w, x, i;
	char buffer[1024], *extra = buffer;

	for (i = 0; i <1024; i++)
		buffer[i] = '\0';
	for (w = 0; aux[w]; w++)
	{
		if (aux[w] != ' ' && aux[w] != '\t')
			break;
	}
	printf("posicion: %i\n", w);
	for (x = 0; aux[x + w]; x++)
	{
		extra[x] = aux[x + w];
	}
	extra[x] = '\0';
	printf("extra: %s", extra);
	printf("Longitudes: aux->%i - extra->%i\n", _strlen(aux), _strlen(extra));
	free(aux);
	return (extra);
		/*while (*string != '\0')
	{
		if (*string != ' ' && *string != '\t')
			break;
		string++;
	}*/
}