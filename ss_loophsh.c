#include "shell.h"

/**
 * fork_cmd - A funtion that forks an executable thread to run command;
 * @info: This refers to the parametre struct
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t  child_pid;

	child_pid = fork();
	if (child_pid == -1) /* The forks is not successful */
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0) /* fork is successful */
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}


/**
 * hsh - A funtion that refers to the main shell loop;
 * @argv: This refers to the arg vector
 * @info: this refers to the parametre struct
 * Return: 0 (on success), 1 (on error), error code
 */

int hsh(info_t *info, char **argv)
{
	/* variable declaration */
	int builtin_return = 0;
	ssize_t a = 0;

	while (a != -1 && builtin_return != -2)
	{
		clear_info(info);
		if (_interactives(info))
			_puts("$ ");
		eputchar(BUF_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, argv);
			builtin_return = find_builtin(info);
			if (builtin_return == -1)
				find_cmd(info);
		}
		else
			if (_interactives(info))
				_putchar('\n');
		free_info(info, 0);
	}
	_write_history(info);
	free_info(info, 1);
	if (!_interactives(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_return);
}

/**
 * find_cmd - A function that finds a command in PATH.
 * @info: This refers to the parametre struct
 * Return: void.
 */

void find_cmd(info_t *info)
{
	/* variable declaration */
	int a, b;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((_interactives(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else
			if (*(info->arg) != '\n')
			{
				info->status = 127;
				print_error(info, "not found\n");
			}
	}
}


/**
 * find_builtin - A function that finds a builtin command;
 * @info: This refers to the parametre struct
 * Return: -1 (if not found), 0 (executed success), 1 (not executed), -2 (exit)
 */

int find_builtin(info_t *info)
{
	int x, built_in_return = -1;
	builtin_table builtintbl[] = {
		{"env", _myenv},
		{"help", _myhelp},
		{"exit", _myexit},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in_return = builtintbl[x].func(info);
			break;
		}
	return (built_in_return);
}


