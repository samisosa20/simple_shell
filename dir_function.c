#include "shell.h"
/**
 * exec_dir - Count lenght of the poniter
 * @argv: direction pointer
 * @string: Pointer to string
 * @bytes_read: size of string
 * Return: None
*/
void exec_dir(char **argv, char *string, ssize_t bytes_read)
{
	pid_t my_pid;

	my_pid = fork();
	if (my_pid == 0)
	{
		get_flags(argv, string, bytes_read);
		if (execve(argv[0], argv, NULL) == -1)
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
 * exec_dir - Count lenght of the poniter
 * @argv: direction pointer
 * @string: function PATH
 * @bytes_read: size of string
 * Return: None
*/
void exec_path(char **argv,char *string, ssize_t bytes_read)
{
	char *path = "/etc/environment";
	int _file, i, j;
	ssize_t _read, _write;
	char *buffer, *aux, *token, *value;
	struct stat stats;

	if (stat(path, &stats) == 0)
	{
		i = stats.st_size;
		aux = malloc(sizeof(char) * i);
		if (aux == NULL)
			free(aux), exit(90);
		buffer = malloc(sizeof(char) * i);
		if (buffer == NULL)
			free(aux), exit(90);
		value = malloc(sizeof(char) * i);
		if (value == NULL)
			free(buffer), free(aux), exit(90);
	}

	_file = open(path, O_RDONLY);
	if (_file == -1)
		free(value), free(buffer), free(aux), exit(90);

	_read = read(_file, buffer, i);
	if (_read == -1)
	{
		close(_file);
		free(value), free(buffer), free(aux), exit(90);
	}
	close(_file);

	while (*buffer != '\0')
	{
		if (*buffer == '/')
		{
			aux = buffer;
			break;
		}
		buffer++;
	}
	aux = strtok(aux, COM_DOU);
	get_flags(argv, string, bytes_read);
	token = strtok(aux, COLON);
	while (token != NULL)
	{
		_strcpy(value, token);
		_strcat(value, SLASH), _strcat(value, string);
		if (stat(value, &stats) == 0)
		{
			for(j = 1; argv[j]; j++)
			{
				_strcat(value, " ");
				_strcat(value, argv[j]);
			}
			exec_dir(argv, value, bytes_read);
			break;
		}
		token = strtok(NULL, COLON);
	}
}