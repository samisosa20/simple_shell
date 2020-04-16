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
	int com_count = 0, nro_error = 0;

	dir_path = _get_path(environ);
	while (1)
	{
		string = NULL, aux = NULL;
		if (isatty(STDIN_FILENO) == 1)
			if (write(0, "$ ", 2) < 0)
				break;
		bytes_read = getline(&string, &size, stdin), com_count++;
		if (bytes_read == EOF)
		{
			free(string);
			break; }
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
		argv = create_mal(size), get_flags(argv, aux);
		argv[0] = _strchr_echo(argv[0], '\"'), aux = _strchr_echo(aux, '\"');
		if (detect_slash('/', aux) == 1 || (aux[0] == '.' && aux[1] == '.' &&
			 aux[2] == '\0'))
			error_perm(aux, av, com_count);
		else
		{
		if (_strchr(aux) == 0)
			nro_error = verify_dir(argv, aux, environ, av, com_count, 1);
		else
			nro_error = exec_path(argv, aux, environ, av, com_count, dir_path); }
		_salir(argv, string); }
	return (nro_error); }
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
/**
* *perror_ex - show error
* @av: name of the program
* @com_count: line run
* @argv: double pointer
* Return: pointer.
*/
void perror_ex(char *av[], int com_count, char **argv)
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
	perror(argv[0]);
}
