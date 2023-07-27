#include "shell.h"

/**
 * _puts - A funtion that prints a string input
 * @str: refers to the dtring to be printed
 * Return: nothing;
 */

void _puts(char *str)
{
	int u = 0;

	if (!str) /* checks if it is a string */
		return;
	while (str[u] != '\0') /* Prints each char of string, excl null byte */
	{
		_putchar(str[u]);
		u++;
	}
}

/**
 * _strdup -A function that duplicates a given string
 * @str: This refers to the string to be duplicated
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int l = 0;
	char *retn;

	if (str == NULL) /*checks if string is empty */
		return (NULL);
	while (*str++)
		l++;
	retn = malloc(sizeof(char) * (l + 1)); /* allocates memory size */
	if (!retn)
		return (NULL);
	for (l++; l--;) /* Duplicates the given string */
		retn[l] = *--str;
	return (retn);
}



/**
 * _putchar - A function that writes the character to stdout
 * @ch: This refers to the char to be printed
 * Return: 1, if success; -1, otherwise, and errno set appropriately.
 */

int _putchar(char ch)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buff[i++] = ch;
	return (1);
}





