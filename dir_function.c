#include "shell.h"
/**
 * exec_dir - execute directory command
 * @argv: direction pointer
 * @string: Pointer to string
 * @bytes_read: size of string
 * Return: None
*/
void exec_dir(char **argv, char *string, ssize_t bytes_read, char **environ)
{
	pid_t my_pid, parent_id;
	
	my_pid = fork();
	if (my_pid == 0)
	{
		get_flags(argv, string, bytes_read);
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("Error2");
			free_mal(argv);
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
char *run_path(char *aux, char *value, char **argv,
				char *string, ssize_t bytes_read, char **environ)
{
	char *token;
	int j;
	struct stat stats;

	get_flags(argv, string, bytes_read);
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
			exec_dir(argv, value, bytes_read, environ);
			break;
		}
		token = strtok(NULL, COLON);
	}
	if (token == NULL)
	{
		write(2, argv[0], _strlen(argv[0]));
		write(2, ": command not found\n", 20);
	}
}
/**
 * exec_path - find command path
 * @argv: direction pointer
 * @string: function PATH
 * @bytes_read: size of string
 * Return: None
*/
void exec_path(char **argv, char *string, ssize_t bytes_read, char **environ)
{
	char *value;
	int _file, i;
	struct stat stats;
	ssize_t _read, _write;
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
	run_path(aux, value, argv, string, bytes_read, environ);
	free(value);
}
