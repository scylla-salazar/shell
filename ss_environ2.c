#include "shell.h"

/**
 * get_environ - A function that returns string array of our environment
 * @info: This refers to the structure, which contains potential arguments
 * Return: 0 (Always).
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed) /* checks for changes in env */
	{
		info->environ = list_to_strings(info->env); /* str array */
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _setenv - A funtion that initialize a new env var, or modify an existing one
 * @var: This refers to the str env variable property
 * @val: This refers to the str env variable value
 * @info: This refers to the structure, which contains potential arguments
 * Return: 0 (Always)
 */

int _setenv(info_t *info, char *var, char *val)
{
	/* initializing some variables */
	char *c;
	list_t *node;
	char *buff = NULL;

	if (!val || !var) /*checks for the str env var property & value */
		return (0);

	buff = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, val);
	node = info->env;
	while (node) /*iterates the node */
	{
		c = _starts_with(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}


/**
 * _unsetenv - A funtion that removes an env variable.
 * @var: Refers to the str env variable property
 * @info: This refers to the structure, which contains the possible arguments
 * Return: 1 (On delete); 0 (if otherwise)
 */

int _unsetenv(info_t *info, char *var)
{
	/* initializing variables */
	list_t *node = info->env;
	char *c;
	size_t i;

	i = 0;
	if (!var || !node) /*checks for the str env var property*/
		return (0);

	while (node) /* iterates the variable, node */
	{
		c = _starts_with(node->str, var);
		if (c && *c == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

