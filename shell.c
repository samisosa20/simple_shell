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
	char *string, *aux;
	int com_count = 0;

	dir_path = _get_path(environ);
	while (1)
	{
		string = NULL, aux = NULL;
		if (isatty(STDIN_FILENO) == 1)
			if (write(0, "$ ", 2) < 0)
				exit(0);
		bytes_read = getline(&string, &size, stdin), com_count++;
		if (bytes_read == EOF)
			free(string), exit(0);
		aux = string;
		while (*aux != '\0')
		{
			if (*aux != ' ' && *aux != '\t')
				break;
			aux++; }
		if (validate_com(aux) == -1)
		{
			free(string);
			continue; }
		argv = create_mal(size);
		get_flags(argv, aux);
		argv[0] = _strchr_echo(argv[0], '\"');
		aux = _strchr_echo(aux, '\"');
		if (detect_slash('/', aux) == 1 || (aux[0] == '.' && aux[1] == '.' &&
			 aux[2] == '\0'))
			error_perm(aux, av, com_count);
		else
		{
		if (_strchr(aux) == 0)
			verify_dir(argv, aux, environ, av, com_count, 1);
		else
			exec_path(argv, aux, environ, av, com_count, dir_path); }
		_salir(argv, string); }
	return (0); }
/**
 * validate_com - validate command
 * @aux: unused.
 * Return: 0 is ok and -1 ko
 */
int validate_com(char *aux)
{
	if (*aux == '\n' || *aux == ' ' || *aux == '\t' ||
		(*aux == '.' && aux[1] == '\n'))
		return (-1);
	return (0);
}
