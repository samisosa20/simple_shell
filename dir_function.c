#include "shell.h"

/**
 * rev_string - isdigit
 * @s: integer
 * Return: prints alphabet
*/
void rev_string(char *s)
{
	int i = 0;
	int len = 0;
	char save = 0;
	int final = 0;

	for (i = 0; s[i] != '\0'; i++)
		len++;
	final = len - 1;

	for (i = final; i >= (final - i); i--)
	{
		save = s[(final - i)];
		s[(final - i)] = s[i];
		s[i] = save;
	}
}

void _itos(long int num, char *string, int cont, int sign)
{
	if (num == 0)
	{
		if (sign == -1)
		{
			string[0] = '-';
			string[1] = '\0';
		}
		else
			string[0] = '\0';
		rev_string(string - cont);
	}
	else
	{
		string[0] = (num % 10) + '0';
		num /= 10;
		_itos(num, string + 1, cont + 1, sign);
	}
}

/**
 * exec_dir - execute directory command
 * @argv: direction pointer
 * @string: Pointer to string
 * @bytes_read: size of string
 * Return: None
*/
void exec_dir(char **argv, char *string, char **environ,
		char *av[], int com_count)
{
	pid_t my_pid;
	
	my_pid = fork();
	if (my_pid == 0)
	{
		get_flags(argv, string);
		if (execve(argv[0], argv, environ) == -1)
		{
			print_error(av, argv, com_count);
			perror(": ");
			free_mal(argv);
			free(string);
			exit(2);
		}
	}
	else if (my_pid > 0)
		wait(0);
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
 * @bytes_read: length string
 * Return: dir path
*/
void run_path(char *aux, char *value, char **argv,
	       char *string, char **environ, char *av[], int com_count)
{
	char *token;
	int j;
	struct stat stats;

	get_flags(argv, string);
	if (_strcmp(argv[0],"exit") == 0)
		_salir(argv, value, string);
	token = strtok(aux, COLON);
	while (token != NULL)
	{
		_strcpy(value, token);
		_strcat(value, SLASH), _strcat(value, string);
		if (stat(value, &stats) == 0)
		{
			for (j = 1; argv[j]; j++)
			{
				_strcat(value, " ");
				_strcat(value, argv[j]);
			}
			exec_dir(argv, value, environ, av, com_count);
			break;
		}
		token = strtok(NULL, COLON);
	}
	if (token == NULL)
	{
		print_error(argv, av, com_count);
		if (write(2, "not found\n", 11) < 0)
			exit (91);
	}
}
/**
 * print_error - print errors
 * @argv: arguments pointer
 * @av: main arguments pointer
 * @com_count: integer number of commands
 * Return: dir path
*/
void print_error(char **argv, char *av[], int com_count)
{
	char com_num[1024];
	
	_itos(com_count, com_num, 0, 1);
	//printf("%s\n", av[0]); ./hsh: 1: qwerty: not found
	if (write(2, av[0], _strlen(av[0])) < 0)
		exit(91);
	if (write(2, ": ", 2) < 0)
		exit(91);
	if (write(2, com_num, _strlen(com_num)) < 0)
		exit(91);
	if (write(2, ": ", 2) < 0)
		exit(91);
	if (write(2, argv[0], _strlen(argv[0])) < 0)
		exit(90);
	if (write(2, ": ", 2) < 0)
		exit(91);
}

/**
 * exec_path - find command path
 * @argv: direction pointer
 * @string: function PATH
 * @bytes_read: size of string
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
