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
