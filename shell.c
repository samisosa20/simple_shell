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
	char **argv, *dir_path, *string, *aux;
	size_t size = 0;
	ssize_t bytes_read = 0;
	int com_count = 0, status_exit = 0;

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
		aux = string, while (*aux != '\0')
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
			error_perm(aux, av, com_count), status_exit = 126;
		else
		{
			if (_strchr(aux) == 0)
				status_exit = verify_dir(argv, aux, environ, av, com_count, 1,
							status_exit);
			else
				status_exit = exec_path(argv, aux, environ, av, com_count, dir_path,
							status_exit); }
		status_exit = _salir(argv, string, status_exit, av, com_count); }
	return (status_exit); }
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
/**
* _isdigit - evaluate if the variable is a digit or not.
* @c: input variable.
* Return: Always 0.
*/
int _isdigit(char *c)
{
	int i;

	for (i = 0; c[i]; i++)
	{
		if (c[i] < 48 || c[i] > 57)
			return (0);
	}
	return (1);
}
