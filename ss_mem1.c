#include "shell.h"


/**
 * ffree - A funtion that frees a string of strings
 * @str: This refers to the string to be freed
 */

void ffree(char **str)
{
	char **ch = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(ch);
}


/**
 * *_memset - A funtion that fills memory with a const byte
 * @p: This rrefers to the ptr to the mem area
 * @b: This refers to the byte to fill *p with
 * @num: This refers to the amt of bytes to be filled
 * Return: p, a ptr to the memory area
 */

char *_memset(char *p, char b, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		p[i] = b;
	return (p);
}


/**
 * _realloc - A function that reallocates a block of mem.
 * @o_size: Refers to the byte size of the previous block
 * @n_size: Refers to the byte of the new block
 * @ptr: This refers to the pointer to prvious mallocted block
 * Return: ptr to the old block
 */


void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	char *a;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == o_size)
		return (ptr);

	a = malloc(n_size);
	if (!a)
		return (NULL);
	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		a[o_size] = ((char *)ptr)[o_size];
	free(ptr);
	return (a);
}

