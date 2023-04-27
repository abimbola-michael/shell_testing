#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct builtin_s - struct used to get builtin function
 * @type: builtin type.
 * @func: pointer to builtin function.
 */
typedef struct builtin_s
{
	char *type;
	void (*func)(char *);
} builtin_t;

/*String Functions*/
int _strcmp(char *, char *);
char *_strdup(char *);
int _strlen(char *);

/*Print Functions*/
void print_str(char *, int);
int print_num(int);
int print_char(char);
void print_error(char *, int, char *);
void print_exec_error(char *, int, char *);

/*Free Pointers Functions*/
void free_single_pointer(int, ...);
void free_double_pointer(char **);

/*Builtin functions*/
void cd(char *);
void exit(char *);
void env(char *);
int get_builtin(char **command, char *arg);

/*Other Functions*/
char **get_tokens(char *, const char *, int);
int count_tokens(char *, const char *);
void create_fork(char **, char *, int, char **);
void parse_command_line(char *, size_t, int, char **);
char *get_command_path(char *);
int search_path(char *);
char *search_directories(char **, char *);
char *build_path(char *, char *);

extern char **environ;

#endif