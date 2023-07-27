#include "shell.h"

/**
 * bfree - A function that free a pointer and nulls the addr
 * @ptr: This refers to the addr of the pointer to be freed
 * Return: 1 (if freed), 0 (otherwise).
 */

int bfree(void **ptr)
{
	if (ptr && *ptr) /* checks if pointer exists */
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


