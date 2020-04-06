#include "shell.h"
/**
 * _strlen - isdigit
 * @s: integer
 * Return: prints alphabet
 */
int _strlen(char *s)
{
	int i;
	int len;

	for (i = 0; s[i] != '\0'; i++)
		len++;
	return (len);
}
/**
 * get_flags - basic shell
 * @string: Pointer to string
 * @bytes_read: size of string
 * Return: prints in screen $ and received commands
 */
void get_flags(char **argv, char *string, ssize_t bytes_read)
{
	char **arguments = argv;
	int i = 0, j = 0;
	char *token = strtok(string, " ");

	while (token != NULL)
	{
		arguments[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	arguments[i] = NULL;
	arguments[i - 1] = strtok(arguments[i - 1], NEW_LINE);
}
/**
 * main - basic shell
 *
 * Return: prints in screen $ and received commands
 */
int main(void)
{
	char **argv;
	pid_t my_pid;
	size_t size = 0;
	ssize_t bytes_read = 0;
	char *string = NULL;
	int i = 0;
	pid_t parent;

	while (1)
	{
		printf("$ ");
		bytes_read = getline(&string, &size, stdin);
		if (bytes_read == -1)
			exit(0);
		if (*string == '\n' || *string == ' ')
		{
			continue;
		}
		argv = malloc(sizeof(char *));
		if (!argv)
			exit(0);
		for (i = 0; argv[i]; i++)
		{
			argv[i] = malloc(sizeof(char) * _strlen(argv[i]) + 1);
			if (!argv[i])
				free(argv), exit(0);
		}
		my_pid = fork();
		if (my_pid == 0)
		{
			parent = getppid();
			get_flags(argv, string, bytes_read);
			if (execve(argv[0], argv, NULL) == -1)
			{
				for (i = 0; argv[i]; i++)
					free(argv[i]);
				free(argv);
				perror("Error2");
			}
			exit(0);
		}
		else if (my_pid > 0)
		{
			wait(0);
			for (i = 0; argv[i]; i++)
				free(argv[i]);
			free(argv);
		}
		else
		{
			for (i = 0; argv[i]; i++)
				free(argv[i]);
			free(argv);
			perror("Error3");
			exit(0);
		}
	}
	return (0);
}