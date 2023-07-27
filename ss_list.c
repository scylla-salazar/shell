#include "shell.h"

/**
 * free_list - A funtion that frees all nodes of a list
 * @hd_ptr: This Refers to addr of pointer to head node
 * Return: void
 */

void free_list(list_t **hd_ptr)
{
	list_t *node, *nxt_node, *hd;

	if (!hd_ptr || !*hd_ptr) /*  */
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*hd_ptr = NULL;
}


/**
 * add_node - A funtion that adds a node to the start of the list
 * @hd: This Refers to addr of pointer to head node
 * @num: This Refers to node index used by history
 * @str: This Refers to string field of node
 * Return: size of list.
 */
list_t *add_node(list_t **hd, const char *str, int num)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = _strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd;
	*hd = new_hd;
	return (new_hd);
}


/**
 * print_list_str - A funtion prints only str element of a list_t linked list
 * @hd: This Refers to ptr to first node
 * Return: size of list, s
 */


size_t print_list_str(const list_t *hd)
{
	size_t s = 0;

	while (hd)
	{
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		s++;
	}
	return (s);
}


/**
 * add_node_end - A funtion that adds a node to the end of the list
 * @hd: This Refers to addr of ptr to head node
 * @num: This Refers to node index used by history
 * @str: This Refers to str field of node
 * Return: size of list.
 */

list_t *add_node_end(list_t **hd, const char *str, int num)
{
	list_t *new, *node;

	if (!hd)
		return (NULL);

	node = *hd;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node) /*  */
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*hd = new;
	return (new);
}


/**
 * delete_node_at_index - A function deletes node at given index
 * @hd: This Refers to addr of pointer to first node
 * @ind: This Refers to index of node to delete
 * Return: 1 (on success), 0 (on failure)
 */

int delete_node_at_index(list_t **hd, unsigned int ind)
{
	list_t *node, *prev;
	unsigned int a = 0;

	if (!hd || !*hd)
		return (0);

	if (!ind) /* check for index  */
	{
		node = *hd;
		*hd = (*hd)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (a == ind)
		{
			prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev = node;
		node = node->next;
	}
	return (0);
}


