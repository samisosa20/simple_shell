#include "shell.h"

/**
 * exec_dir - execute directory command
 * @argv: direction pointer
 * @string: Pointer to string
 * @environ: double pointer
 * @av: command
 * @com_count: nro of line
 * @flag: know who call
 * Return: None
*/
void exec_dir(char **argv, char *string, char **environ,
		 char *av[], int com_count, int flag)
{
	pid_t my_pid;
	char *aux;
	int j;

	if (flag == 1)
		aux = string;
	else
		aux = argv[0];
	my_pid = fork();
	if (my_pid == 0)
	{
		argv[0] = aux;

		for (j = 1; argv[j]; j++)
		{
			argv[j] = _strchr_echo(argv[j], '\"');
		}
		if (execve(string, argv, environ) == -1)
		{
			error_ex(string, av, com_count);
			free_mal(argv);
			free(string);
			exit(126);
		}
	}
	else if (my_pid > 0)
	{
		if (wait(0) < 0)
			perror("Error4");
	}
	else
	{
		perror("Error3"); /*corregir mensaje de salida*/
		exit(1);
	}
}
/**
 * run_path - run dir path
 * @value: direction pointer
 * @aux: direction PATH
 * @argv: direction double pointer
 * @string: command PATH
 * @environ: double pointer
 * @av: command
 * @com_count: nro of line
 * Return: dir path
*/
void run_path(char *aux, char *value, char **argv,
		   char *string, char **environ, char *av[], int com_count)
{
	char *token;
	struct stat stats;

	if (_strcmp(argv[0], "exit") == 0)
		_salir(argv, value, string);
	token = strtok(aux, COLON);
	while (token != NULL)
	{
		_strcpy(value, token);
		_strcat(value, SLASH), _strcat(value, argv[0]);
		if (stat(value, &stats) == 0)
		{
			argv[0] = value;
			exec_dir(argv, value, environ, av, com_count, 2);
			break;
		}
		token = strtok(NULL, COLON);
	}
	if (token == NULL)
	{
		print_error(argv, av, com_count);
		if (write(2, "not found\n", 11) < 0)
			exit(127);
	}
}

/**
 * exec_path - find command path
 * @argv: direction pointer
 * @string: function PATH
 * @environ: double pointer
 * @av: command
 * @com_count: nro of line
 * Return: None
*/
void exec_path(char **argv, char *string, char **environ,
		char *av[], int com_count)
{
	char *value;
	int _file, i;
	struct stat stats;
	ssize_t _read;
	char buffer[1024], *aux, *extra = buffer;

	if (stat(PATH_DIR, &stats) == 0)
	{
		i = stats.st_size;
		value = malloc(sizeof(char) * i);
		if (value == NULL)
			exit(90);
	}
	_file = open(PATH_DIR, O_RDONLY);
	if (_file == -1)
		free(value), exit(90);

	_read = read(_file, buffer, i);
	if (_read == -1)
		close(_file), free(value), exit(90);
	close(_file);

	while (*extra != '\0')
	{
		if (*extra == '/')
		{
			aux = extra;
			break;
		}
		extra++;
	}
	aux = strtok(aux, COM_DOU);
	run_path(aux, value, argv, string, environ, av, com_count);
	free(value);
}
