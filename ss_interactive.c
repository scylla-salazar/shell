#include "shell.h"

/**
 * _interactives - A programme that returns true if shell is interactive
 * @info: This refers to the struct address
 * Return: 1 (if interactive mode); 0 (if otherwise)
 */

int _interactives(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 * _isalpha - A function that checks if a given input is an alphabet
 * @ch: This is the character to be checked
 * Return: 1 (if ch is an alphabet); 0 (if not an alphabet)
 */

int _isalpha(int ch)
{
	/* Checks for alphabet characters */
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	else
		return (0);
}


/**
 * is_delim - A funtion that checks if a given character is a delimeter
 * @delm: Refers to the delimeter str.
 * @ch: Refers to the character to be checked
 * Return: 1 (if true), 0 (if false)
 */

int is_delim(char ch, char *delm)
{
	while (*delm)
		if (*delm++ == ch)
			return (1);
	return (0);
}


/**
 * _strtoint - A function that converts a str to an int.
 * @str: This refers to the str to be converted to an int.
 * Return: Converted number; 0 (if no numbers in str).
 */

int _strtoint(char *str)
{
	int a, outputs;
	int flags = 0;
	unsigned int outcome = 0;
	int sign = 1;

	for (a = 0; str[a] != '\0' && flags != 2; a++)
	{
		if (str[a] == '-')
			sign *= -1;
		if (str[a] >= '0' && str[a] <= '9')
		{
			outcome *= 10;
			flags = 1;
			outcome += (str[a] - '0');
		}
		else
			if (flags == 1)
				flags = 2;
	}

	if (sign == -1) /* affixes the sign */
		outputs = -outcome;
	else
		outputs = outcome;

	return (outputs);
}

