#include "shell.h"
/**
 * main - basic shell
 *
 * Return: prints in screen $ and received commands
 */
int main(void)
{
	char *argv[] = {"", NULL};
	pid_t my_pid;
	size_t size = 0;
	ssize_t bytes_read = 0;
	char *string = NULL;

	while (1)
	{
		printf("$ ");
		string = (char *)malloc(size);
		if (string == NULL)
		{
			free(string);
			continue;
		}
		bytes_read = getline(&string, &size, stdin);
		if (bytes_read == -1)
			exit(0); /*recordar que aquí debe haber un posible perror*/
		my_pid = fork();
		if (my_pid == 0)
		{
			if (*string == '\n')
				break;
			if (execve(strtok(string, NEW_LINE), argv, NULL) == -1)
				perror("Error2");
			exit(0);
		}
		else if (my_pid > 0)
			wait(NULL);
		else
			perror("Error3");
		free(string);
	}
	return (0);
}
