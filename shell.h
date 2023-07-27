#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define USE_GETLINE 0
#define USE_STRTOK 0

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

extern char **environ;

/**
 * struct liststr - the singly linked list
 * @num: the num field
 * @str: refers a str
 * @next: this points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 *
 *struct passinfo - This contain pseudo-args to pass into a funct
 *@arg: Refers a str generated from getline containing args
 *@argv: Refers to an array of str generated from arg
 *@path: Refers to str path for the current cmd
 *@argc: Refers to the arg count
 *@env: refers to linked list local copy of environ
 *@environ: refrs to custom modified copy of environ from LL env
 *@history: refers to the hist node;
 *@err_num: refers to the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: refers to the program filename
 *@histcount: the history line num count
 *@cmd_buf: addr of ptr to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@alias: refers to the alias node;
 *@env_changed: on, if environ was changed
 *@status: referrs to the return status of the last exec'd command
 *@line_count: refers to the error count;
 *@readfd: refers the fd from which to read line input
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type; 
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - This contains a builtin str & related function
 *@type: Refers to the builtin command flag
 *@func: refers to the function
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;



int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _populate_envlist(info_t *);
char *_getenv(info_t *, const char *);

char *_get_historyfile(info_t *info);
int _write_history(info_t *info);
int _read_history(info_t *info);
int _build_historylist(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

int is_delim(char, char *);
int _strtoint(char *);
int _isalpha(int);
int _interactives(info_t *);

int _putfd(char ch, int);
int _putsfd(char *str, int);
int eputchar(char);
void _eput(char *);

void _puts(char *);
char *_strdup(const char *);
int _putchar(char);

char *_starts_with(const char *, const char *);
int _strlen(char *);
int _strcmp(char *, char *);

char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

char **_strtok1(char *, char);
char **_strtok2(char *, char *);

char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

void _sig_intHandler(int);
ssize_t read_buf(info_t *, char *, size_t *);
ssize_t get_input(info_t *);
ssize_t input_buf(info_t *, char **, size_t *);
int _getline(info_t *, char **, size_t *);

void fork_cmd(info_t *);
int hsh(info_t *, char **);
void find_cmd(info_t *);
int find_builtin(info_t *);

char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);

int bfree(void **);

void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

int _myhelp(info_t *);
int _myexit(info_t *);
int _mycd(info_t *);

int _erratoi(char *);
void print_error(info_t *, char *);
void remove_comments(char *);
int print_d(int, int);
char *convert_number(long int, int, int);

int _myalias(info_t *);
int _myhistory(info_t *);
int set_alias(info_t *, char *);
int unset_alias(info_t *, char *);
int print_alias(list_t *);

void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);

list_t *node_starts_with(list_t *, char *, char);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);

int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

int main(int, char **);

#endif
