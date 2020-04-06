#include "shell.h"
/**
 * _strlen - A function to count the lenght of an array
 * @s : array
 * Return: an int of the lenght of an array
 */

int _strlen(char *s)
{
	int m = 0;
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		m = m + 1;
	}
	return (m);
}
/**
 * *_strcpy - Return the copy of an string
 * @dest : an array
 * @src : an array
 * Return: an array
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * get_flags - basic shell
 * @string: Pointer to string
 * @bytes_read: size of string
 * Return: prints in screen $ and received commands
 */
char **get_flags(char *string, int size)
{
	char **arguments;
	int i = 0, j = 0;
	char *token;
	char copy[100];

	printf("%s\n", _strcpy(copy, string));
	token = strtok(copy, " ");
	while (token != NULL)
	{
		token = strtok(NULL, " ");
		j++;
	}
	token = strtok(string, " ");
	arguments = malloc(sizeof(char *) * size);
	while (token != NULL)
	{		
		arguments[i] = malloc(sizeof(char) * _strlen(token));
		arguments[i] = token;
		printf("token get_flags = %s\n", token);
		token = strtok(NULL, " ");
		i++;
	}
	arguments[i] = NULL;
	arguments[i - 1] = strtok(arguments[i - 1], NEW_LINE);
	return (arguments);
}
/**
 * get_flags - basic shell
 * @string: Pointer to string
 * @bytes_read: size of string
 * Return: prints in screen $ and received commands
 */
int _size(char *string)
{
	int j = 0;
	char *token;
	char copy[1024];

	_strcpy(copy, string);
	token = strtok(copy, " ");
	while (token != NULL)
	{
		printf("token size = %s\n", token);
		token = strtok(NULL, " ");
		j++;
	}	
	return (j);
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
	int i = 0, j = 0;

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
		{
			free(string);
			exit(0); /*recordar que aquí debe haber un posible perror*/
		}
		j = _size(string);
		argv = get_flags(string, j);
		my_pid = fork();
		if (my_pid == 0)
		{
			
			if (*string == '\n' || *string == ' ')
			{
				free(string);
				break;
			}
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error2");
			}
		}
		else if (my_pid > 0)
			wait(NULL);
		else
			perror("Error3");
		for (; j >= 0; j--)
		{
			printf("final = %s\n", argv[j]);
			//free(argv[j]);
		}
		free(argv);
		free(string);
	}
	return (0);
}
