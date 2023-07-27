#include "shell.h"

/**
 * *_starts_with - A function that checks if a string starts with a substring
 * @substr: This refers to the string to search for
 * @str: This refers to the string to search
 * Return: NULL or the address of the substring.
 */

char *_starts_with(const char *str, const char *substr)
{
	while (*substr)
		if (*substr++ != *str++) /* NULL, if substring not in string */
			return (NULL);
	return ((char *)str); /* Returns the address of the substring */
}


/**
 * _strlen - A funtion that returns the length of a given string
 * @str: This refers to the string to be checked
 * Return: length of the string (ineteger) or 0 if not string
 */

int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++) /* check the number of characters of the string */
		i++;
	return (i);
}

/**
 * _strcmp - A function that performs comparison of two strings
 * @str1: This refers tithe first string
 * @str2: This refers to the second string
 * Return: negative if str1 < str2;
 *         positive if str1 > str2; zero if str1 = str
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2) /* Logic comparison of the two strings */
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2) /*returns 0 if both string are the same */
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1); /* return negative value,*/
}

