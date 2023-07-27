#include "shell.h"


/**
 * _erratoi - a funtion that converts a str to an int
 * @str: This refers to the str to be converted
 * Return: 0 (if no number in string), converted number, -1 (on error)
 */

int _erratoi(char *str)
{
	int u = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;
	for (u = 0; str[u] != '\0'; u++)
	{
		if (str[u] <= '9' && str[u] >= '0')
		{
			r *= 10;
			r += (str[u] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}


/**
 * print_error - A function that prints an error message
 * @str: This refers to the str containing the specified type of error
 * @info: This refers to the parametre struct
 * Return: error message
 */

void print_error(info_t *info, char *str)
{
	_eput(info->fname);
	_eput(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eput(": ");
	_eput(info->argv[0]);
	_eput(": ");
	_eput(str);
}


/**
 * remove_comments - A function replaces the first occurrence of '#' with '\0'
 * @buff: This refers to the addr of the str to modify
 */

void remove_comments(char *buff)
{
	int a;

	for (a = 0; buff[a] != '\0'; a++)
		if (buff[a] == '#' && (!a || buff[a - 1] == ' '))
		{
			buff[a] = '\0';
			break;
		}
}


/**
 * print_d - A funtion that prints a decimal (integer) number (base 10)
 * @inp: this Refers to the input
 * @fds: This Refers to the filedescriptor to be written to
 * Return: no of characters printed.
 */

int print_d(int inp, int fds)
{
	int (*__putchar)(char) = _putchar;
	int a, cnt = 0;
	unsigned int _abs_, cur;

	if (fds == STDERR_FILENO)
		__putchar = eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = inp;
	cur = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + cur / a);
			cnt++;
		}
		cur %= a;
	}
	__putchar('0' + cur);
	cnt++;

	return (cnt);
}


/**
 * convert_number - A funtion that converter function, a clone of itoa
 * @base: This Refers to the base
 * @flag: This refers to arg flags.
 * @num: This Refers to the number.
 * Return: string.
 */

char *convert_number(long int num, int base, int flag)
{
	static char *array;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long t = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		t = -num;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = array[t % base];
		t /= base;
	} while (t != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

