#include "shell.h"


/**
 * replace_string - A funtion replaces string
 * @new_str: this Refers to the new str
 * @old_str: this Refers to the address of old str
 * Return: 1 (if replaced), 0 (if otherwise)
 */

int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}


/**
 * is_chain - A funtion that tests if current char in buffer is a chain delim
 * @info: This Refers to the parametre struct;
 * @pt: This Refers to addr of current position in buf;
 * @buff: This Refers to the char buffer
 * Return: 1 (if chain delim),  0 (if  otherwise)
 */

int is_chain(info_t *info, char *buff, size_t *pt)
{
	size_t d = *pt;

	if (buff[d] == '|' && buff[d + 1] == '|')
	{
		buff[d] = 0;
		d++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[d] == '&' && buff[d + 1] == '&')
	{
		buff[d] = 0;
		d++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[d] == ';')
	{
		buff[d] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pt = d;
	return (1);
}


/**
 * replace_alias - A funtion that replaces an aliases in the tokenized str
 * @info: This Refers to the parameter struct;
 * Return: 1 (if replaced), 0 (if  otherwise)
 */


int replace_alias(info_t *info)
{
	int t;
	list_t *node;
	char *pt;

	for (t = 0; t < 10; t++) /* Iterating for ten times*/
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pt = _strchr(node->str, '=');
		if (!pt)
			return (0);
		pt = _strdup(pt + 1);
		if (!pt)
			return (0);
		info->argv[0] = pt;
	}
	return (1);
}


/**
 * replace_vars - A funtion that replaces vars in the tokenized str
 * @info: This Refers to the parameter struct
 * Return: 1 (if replaced) 0 (if otherwise)
 */

int replace_vars(info_t *info)
{
	/* variable declaration */
	int z = 0;
	list_t *node;

	for (z = 0; info->argv[z]; z++)
	{
		if (info->argv[z][0] != '$' || !info->argv[z][1])
			continue;

		if (!_strcmp(info->argv[z], "$?"))
		{
			replace_string(&(info->argv[z]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[z], "$$"))
		{
			replace_string(&(info->argv[z]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[z][1], '=');
		if (node)
		{
			replace_string(&(info->argv[z]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[z], _strdup(""));

	}
	return (0);
}


/**
 * check_chain - funtion checks we shld continue chaining based on last status
 * @info: This Refers to the parameter struct
 * @l: This Refers to length of buffer
 * @buff: This Refers to the char buffer
 * @pt: This Refers to addr of current position in buff;
 * @i: This Refers to the starting position in buff;
 * Return: Void
 */


void check_chain(info_t *info, char *buff, size_t *pt, size_t i, size_t l)
{
	size_t k = *pt;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			k = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			k = l;
		}
	}

	*pt = k;
}


