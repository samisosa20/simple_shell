#include "shell.h"

/**
 * main - basic shell
 *
 * Return: prints in screen $ and received commands
 */
int main(int argc, char *av[], char **environ)
{
	pid_t my_pid;
	char **argv;
	size_t size = 0;
	ssize_t bytes_read = 0;
	char *string = NULL;
	int i = 0;
	pid_t parent_id;

	while (1)
	{
		if (write(0, "$ ", 2) < 0)
			exit(0);
		bytes_read = getline(&string, &size, stdin);
		if (bytes_read == EOF)
			free(string), exit(5);
		if (*string == '\n' || *string == ' ' || *string == '\t')
			continue;
		argv = create_mal(size);
		if (_strchr(string) == 0)
			exec_dir(argv, string, bytes_read, environ);
		else
			exec_path(argv, string, bytes_read, environ);
		free_mal(argv);
	}
	return (0);
}
