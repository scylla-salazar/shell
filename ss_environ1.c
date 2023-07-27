#include "shell.h"

/**
 * _myenv - a funtion that prints the current environment ;
 * @info: This refers to the structure containing possible arguments.
 * Return: 0 (Always)
 */

int _myenv(info_t *info)
{
	print_list_str(info->env); /*prints the current environmrnt */
	return (0);
}


/**
 * _mysetenv - A funtion that initializes a new env variable, modifies existing
 * @info: This refers to the structure, contain possible arguments.
 * Return: 0 (On success); 1 (On failure)
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eput("Incorrect number of argments\n"); /* error message */
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2])) /* initializ the env*/
		return (0);
	return (1);
}

/**
 * _myunsetenv - A funtion that removes the environment variable.
 * @info: This refers to the structure; which contains possible arguments
 *
 * Return: 0 (On success); 1 (On failure).
 */


int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eput("Very few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}


/**
 * _populate_envlist - A function that populates evironment linked list
 * @info: This refers to the structure, which contains possible arguments
 * Return: 0 (Always)
 */

int _populate_envlist(info_t *info)
{
	size_t p;
	list_t *node = NULL;

	for (p = 0; environ[p]; p++)
		add_node_end(&node, environ[p], 0);
	info->env = node;
	return (0);
}



/**
 *_getenv - A funtion tthat gets the value of an environmental variable;
 *@names: This refers to the environment variable name
 *@info: This refers to the structure, which contains possible arguments
 *Return: the value of the environ variable.
 */

char *_getenv(info_t *info, const char *names)
{
	char *i;
	list_t *node = info->env;

	while (node)
	{
		i = _starts_with(node->str, names);
		if (i && *i) /* value of the env var */
			return (i);
		node = node->next;
	}
	return (NULL);
}

