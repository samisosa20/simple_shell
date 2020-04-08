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
void get_flags(char **argv, char *string, ssize_t bytes_read);
int _strchr(char *s);
char **create_mal(size_t size);
void free_mal(char **argv);
void exec_dir(char **argv, char *string, ssize_t bytes_read);
void exec_path(char **argv, char *string, ssize_t bytes_read);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *run_path(char *aux, char *value, char **argv, char *string, ssize_t bytes_read);
#endif
