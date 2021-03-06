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
int exec_dir(char **argv, char *string, char **environ,
				char *av[], int com_count, int flag);
int verify_dir(char **argv, char *string, char **environ,
	      char *av[], int com_count, int flag, int status_exit);
int exec_path(char **argv, char *string, char **environ,
				char *av[], int com_count, char *dir_path, int status_exit);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int run_path(char *aux, char *value, char **argv, char *string,
				char **environ,
				char *av[], int com_count, char *copy_path, int status_exit);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
int _salir(char **argv, char *string, int status_exit,
				char *av[], int com_count);
void print_error(char **argv, char *av[], int com_count);
void error_ex(char *string, char *av[], int com_count);
void _itos(long int num, char *string, int cont, int sign);
char *_strchr_echo(char *s, char c);
char *_get_path(char **environ);
int detect_slash(char c, char *string);
void error_perm(char *string, char *av[], int com_count);
int validate_com(char *aux);
char *_clean_line(char *aux);
void perror_ex(char *av[], int com_count, char **argv);
int _isdigit(char *c);
#endif
