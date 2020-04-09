#ifndef SHELL_H
#define SHELL_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define NEW_LINE "\n"
#define SLASH "/"
#define COM_DOU "\""
#define COLON ":"
#define PATH_DIR "/etc/environment"
int _strlen(char *s);
void get_flags(char **argv, char *string);
int _strchr(char *s);
char **create_mal(size_t size);
void free_mal(char **argv);
void exec_dir(char **argv, char *string, char **environ,
				char *av[], int com_count);
void exec_path(char **argv, char *string, char **environ,
				char *av[], int com_count);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
void run_path(char *aux, char *value, char **argv, char *string,
				char **environ, char *av[], int com_count);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
void _salir(char **argv, char *value, char *string);
void print_error(char **argv, char *av[], int com_count);
void error_ex(char **argv, char *av[], int com_count);
void _itos(long int num, char *string, int cont, int sign);
#endif
