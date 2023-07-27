#include "shell.h"


/**
 * node_starts_with - A funtion that returns node whose str starts with prefix
 * @ch: This refers to the next char after prefix to match
 * @node: This Refers to the pointer to list head
 * @strn: Refers to the string to match
 * Return: match node, or null
 */


list_t *node_starts_with(list_t *node, char *strn, char ch)
{
	char *t = NULL;

	while (node) /* Iterates the node */
	{
		t = _starts_with(node->str, strn);
		if (t && ((ch == -1) || (*t == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * print_list - A funtion that prints all elements of a list_t linked list
 * @hd: This Refers to the pointer to 1st node
 * Return: size of list, t
 */

size_t print_list(const list_t *hd)
{
	size_t t = 0;

	while (hd) /* interates the pointer */
	{
		_puts(convert_number(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		t++;
	}
	return (t);
}


/**
 * get_node_index - A funtion that gets the index of a node
 * @hd: This Refers to the ptr to list head
 * @node: This Refers to the ptr to the node
 * Return: index of node, or -1 (if otherwise)
 */


ssize_t get_node_index(list_t *hd, list_t *node)
{
	size_t q = 0;

	while (hd)
	{
		if (hd == node)
			return (q);
		hd = hd->next;
		q++;
	}
	return (-1);
}


/**
 * list_len - A function that determines length of linked list
 * @hd: This Refers to pointer to 1st node
 * Return: size of list, s
 */


size_t list_len(const list_t *hd)
{
	size_t s = 0;

	while (hd)
	{
		hd = hd->next;
		s++;
	}
	return (s);
}



/**
 * list_to_strings - A function that returns an array of str of the list->str
 * @hd: This Refers to the pointer to 1st node
 * Return: array of strings.
 */


char **list_to_strings(list_t *hd)
{
	list_t *node = hd;
	size_t s = list_len(hd), t;
	char **strs;
	char *str;

	if (!hd || !s)
		return (NULL);
	strs = malloc(sizeof(char *) * (s + 1));
	if (!strs)
		return (NULL);
	for (s = 0; node; node = node->next, s++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (t = 0; t < s; t++)
				free(strs[t]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[s] = str;
	}
	strs[s] = NULL;
	return (strs);
}



