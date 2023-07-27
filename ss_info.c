#include "shell.h"

/**
 * clear_info - A funtion that clears info_t struct;
 *
 * @info: This refers to the struct addr.
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * free_info - A funtion that frees info_t struct
 * @all: this is true, if freeing all fields
 * @info: refers to the struct addr.
 */

void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all) /* checks for if freeing all fields */
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->alias)
			free_list(&(info->alias));
		if (info->history)
			free_list(&(info->history));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * set_info - A function that initializes info_t
 * @argv: This refers to the argument vector;
 * @info: This refers to the struct addr
 */

void set_info(info_t *info, char **argv)
{
	int i = 0;

	info->fname = argv[0];

	if (info->arg)
	{
		info->argv = _strtok2(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			info->argc = i;
		replace_alias(info);
		replace_vars(info);
	}
}

