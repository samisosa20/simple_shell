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
void verify_dir(char **argv, char *string, char **environ,
		  char *av[], int com_count, int flag)
{
	struct stat stats;

	if (stat(argv[0], &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode) == 0)
			exec_dir(argv, string, environ, av, com_count, flag);
		else
		{
			print_error(argv, av, com_count);
			if (write(2, "Permission denied\n", 18) < 0)
				exit(127);
		}
	}
	else
	{
		print_error(argv, av, com_count);
		if (write(2, "not found\n", 10) < 0)
			exit(127);
	}
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
		for (j = 0; argv[j]; j++)
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
		perror("Error3");
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
 * @copy_path: copy path
 * Return: dir path
*/
void run_path(char *aux, char *value, char **argv,
		   char *string, char **environ,
		   char *av[], int com_count, char *copy_path)
{
	char *token, pwd[] = "./";
	struct stat stats;
	int bandera;

	if (_strcmp(argv[0], "exit") == 0)
		_salir(argv, value, string, copy_path);
	_strcpy(copy_path, aux);
	bandera = 0;
	if (*copy_path == ':')
		bandera = 1;
	token = strtok(copy_path, COLON);
	while (token != NULL)
	{
		if (bandera == 1)
		{
			_strcat(value, pwd), _strcat(value, argv[0]);
		}
		else
		{
			_strcpy(value, token);
			_strcat(value, SLASH), _strcat(value, argv[0]);
		}
		bandera = 0;
		if (stat(value, &stats) == 0)
		{
			exec_dir(argv, value, environ, av, com_count, 2);
			break;
		}
		token = strtok(NULL, COLON);
	}
	if (token == NULL)
	{
		print_error(argv, av, com_count);
		if (write(2, "not found\n", 10) < 0)
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
 * @dir_path: dir path
 * Return: None
*/
void exec_path(char **argv, char *string, char **environ,
		char *av[], int com_count, char *dir_path)
{
	char *value = NULL, *copy_path = NULL;

	value = malloc(sizeof(char) * _strlen(dir_path) + _strlen(string));
	if (value == NULL)
		exit(90);
	copy_path = malloc(sizeof(char) * _strlen(dir_path) + _strlen(string));
	if (copy_path == NULL)
		exit(90);
	run_path(dir_path, value, argv, string, environ,
			av, com_count, copy_path);
	free(value);
	free(copy_path);
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
