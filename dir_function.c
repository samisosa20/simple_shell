#include "shell.h"

/**
 * verify_dir - execute directory command
 * @argv: direction pointer
 * @string: Pointer to string
 * @environ: double pointer
 * @av: command
 * @com_count: nro of line
 * @flag: know who call
 * Return: None
*/
int verify_dir(char **argv, char *string, char **environ,
		  char *av[], int com_count, int flag)
{
	struct stat stats;
	int status_exit = 0;

	if (stat(argv[0], &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode) == 0)
			status_exit = exec_dir(argv, string, environ, av, com_count, flag);
		else
		{
			print_error(argv, av, com_count);
			if (write(2, "Permission denied\n", 18) < 0)
				return (127);
			return (126);
		}
	}
	else
	{
		print_error(argv, av, com_count);
		if (write(2, "not found\n", 10) < 0)
			return (127);
	}
	return (status_exit);
}

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
int exec_dir(char **argv, char *string, char **environ,
		 char *av[], int com_count, int flag)
{
	pid_t my_pid;
	char *aux;
	int j, status_exit = -1;

	if (flag == 1)
		aux = string;
	else
		aux = argv[0];
	my_pid = fork();
	if (my_pid == 0)
	{
		argv[0] = aux;
		for (j = 0; argv[j]; j++)
		{
			argv[j] = _strchr_echo(argv[j], '\"');
		}
		if (execve(string, argv, environ) == -1)
		{
			error_ex(string, av, com_count);
			free_mal(argv);
			free(string);
			exit(126); }
	}
	else if (my_pid > 0)
	{
		if (wait(&status_exit) < 0)
		{
			perror_ex(av, com_count, argv);
			return (2); }
	}
	else
	{
		perror_ex(av, com_count, argv);
		return (2); }
	return (status_exit / 255);
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
 * @copy_path: copy path
 * Return: dir path
*/
int run_path(char *aux, char *value, char **argv,
		   char *string, char **environ,
		   char *av[], int com_count, char *copy_path)
{
	char *token, pwd[] = "./";
	struct stat stats;
	int bandera, status_exit = 0;

	_strcpy(copy_path, aux);
	bandera = 0;
	if (*copy_path == ':')
		bandera = 1;
	else if (string[0] == '.' && string[1] == '/')
		bandera = 2;
	token = strtok(copy_path, COLON);
	while (token != NULL)
	{
		if (bandera == 1)
			_strcat(value, pwd), _strcat(value, argv[0]);
		else if (bandera == 2)
			value = argv[0];
		else
		{
			_strcpy(value, token);
			_strcat(value, SLASH), _strcat(value, argv[0]);
		}
		bandera = 0;
		if (stat(value, &stats) == 0)
		{
			status_exit = exec_dir(argv, value, environ, av, com_count, 2);
			break; }
		token = strtok(NULL, COLON);
	}
	if (token == NULL)
	{
		if (_strcmp(argv[0], "exit") != 0)
		{
			print_error(argv, av, com_count);
			if (write(2, "not found\n", 10) < 0)
				exit(127);
			return (127);
		}
	}
	return (status_exit);
}

/**
 * exec_path - find command path
 * @argv: direction pointer
 * @string: function PATH
 * @environ: double pointer
 * @av: command
 * @com_count: nro of line
 * @dir_path: dir path
 * Return: None
*/
int exec_path(char **argv, char *string, char **environ,
		char *av[], int com_count, char *dir_path)
{
	char *value = NULL, *copy_path = NULL;
	int status_exit = 0;

	value = malloc(sizeof(char) * _strlen(dir_path) + _strlen(string));
		if (value == NULL)
			exit(90);
		copy_path = malloc(sizeof(char) * _strlen(dir_path) + _strlen(string));
		if (copy_path == NULL)
			exit(90);
	status_exit = run_path(dir_path, value, argv, string, environ,
			av, com_count, copy_path);
	free(value);
	free(copy_path);
	return (status_exit);
}

/**
* _strchr_echo - a function that locates a character in a string
* @s: pointer that locate a character.
* @c: character.
* Return: pointer.
*/
char *_strchr_echo(char *s, char c)
{
	if (*s == c)
		s = strtok(s, "\"");
	return (s);
}
