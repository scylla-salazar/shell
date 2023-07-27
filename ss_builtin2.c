#include "shell.h"

/**
 * _myalias - A funtion that mimics the alias builtin
 * @info: This Refers to the Struct, containing potential args
 *
 *  Return: 0 (Always)
 */


int _myalias(info_t *info)
{
	/* Variable declaration */
	int p = 0;
	char *y = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (p = 1; info->argv[p]; p++)
	{
		y = _strchr(info->argv[p], '=');
		if (y)
			set_alias(info, info->argv[p]);
		else
			print_alias(node_starts_with(info->alias, info->argv[p], '='));
	}

	return (0);
}

/**
 * _myhistory - A funct disp the hist list, one cmd by line,with line nos, st 0
 * @info: This Refers to the Struct; containing potential args
 *  Return: 0 (Always)
 */


int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


/**
 * set_alias - A funtion that sets alias to str
 * @str: This Refers to the str alias
 * @info: This Refers to parametre struct
 * Return: 0 (on success), 1 (on error)
 */


int set_alias(info_t *info, char *str)
{
	char *ch;

	ch = _strchr(str, '=');
	if (!ch)
		return (1);
	if (!*++ch)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * unset_alias - A funtion that removes alias from str
 * @str: Thid Refers to the str alias
 * @info: This Refers to parametre struct
 * Return: 0 (on success), 1 (on error)
 */


int unset_alias(info_t *info, char *str)
{
	/* Variable declaration */
	char *o, p;
	int q;

	o = _strchr(str, '=');
	if (!o)
		return (1);
	p = *o;
	*o = 0;
	q = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*o = p;
	return (q);
}


/**
 * print_alias - A funtion that prints an alias str
 * @node: This Refers to the alias node
 * Return: Always 0 (if success), 1 (on error)
 */


int print_alias(list_t *node)
{
	char *g = NULL, *h = NULL;

	if (node)
	{
		g = _strchr(node->str, '=');
		for (h = node->str; h <= g; h++) /*iterates the elemnts of st*/
			_putchar(*h);
		_putchar('\'');
		_puts(g + 1);
		_puts("'\n");
		return (0);
	}
	return (1); /* on error */
}

