#include "shell.h"

/**
 * _putfd - A function that writes the character ch to file descriptor
 * @fds: This refers to the file descriptor to be written to
 * @ch: This refers to the character to be printed
 * Return: 1 (On Succes); -1 (On error, & errno set appropriately)
 */

int _putfd(char ch, int fds)
{
	static char buff[WRITE_BUF_SIZE];
	static int u;

	if (ch == BUF_FLUSH || u >= WRITE_BUF_SIZE) /* Testing the conditions */
	{
		write(fds, buff, u);
		u = 0;
	}
	if (ch != BUF_FLUSH)
		buff[u++] = ch;
	return (1);
}


/**
 * _putsfd - A function the prints a given string
 * @fds: This refers to the file descriptor to be written to
 * @str: This refers to the str to be printed
 * Return: The no of chars printed
 */

int _putsfd(char *str, int fds)
{
	int u;

	u = 0;
	if (!str)
		return (0);
	while (*str) /* prints the given string */
	{
		u += _putfd(*str++, fds);
	}
	return (u);
}


/**
 * eputchar - A funtion that writes a given character to standard error
 * @ch: This refers to the character to be written to stderr
 * Return: 1 (On success); -1 (On error, & errno set appropriately)
 */

int eputchar(char ch)
{
	static char buff[WRITE_BUF_SIZE];
	static int i;

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buff, i); /* writes the up to thr count byte i */
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buff[i++] = ch; /* append the given char to the buffer */
	return (1);
}


/**
 * _eput - A function thst printd a given string
 * @str: Thiss refers to the str to be printed;
 * Return: nothing;
 */

void _eput(char *str)
{
	int i;

	i = 0;
	if (!str) /* checks if str exists */
		return;
	while (str[i] != '\0')
	{
		eputchar(str[i]); /* prints the given string */
		i++;
	}
}


