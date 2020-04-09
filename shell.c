#include "shell.h"

/**
 * main - basic shell
 *
 * Return: prints in screen $ and received commands
 */
int main(__attribute__((unused)) int argc, char *av[], char **environ)
{
	char **argv;
	size_t size = 0;
	ssize_t bytes_read = 0;
	char *string = NULL;
	int com_count = 0;

	while (1)
	{
		if (write(0, "$ ", 2) < 0)
			exit(0);
		bytes_read = getline(&string, &size, stdin);
		com_count++;
		if (bytes_read == EOF)
			free(string), exit(5);
		if (*string == '\n' || *string == ' ' || *string == '\t')
			continue;
		argv = create_mal(size);
		if (_strchr(string) == 0)
			exec_dir(argv, string, environ, av, com_count);
		else
			exec_path(argv, string, environ, av, com_count);
		free_mal(argv);
	}
	return (0);
}
