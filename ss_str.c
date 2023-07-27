#include "shell.h"

/**
 * _strcat - A funtion that concatenates two strings
 * @sc: Refers to the source buffer
 * @dstn: Refers to the destination buffer
 * Return: A pointer to the destination buffer
 */

char *_strcat(char *dstn, char *sc)
{
	char *retn = dstn;

	while (*dstn)
		dstn++;
	while (*sc)
		*dstn++ = *sc++;
	*dstn = *sc;

	return (retn);
}

/**
 * _strcpy - A funtion that copies a string
 * @sc: This refers to the source string (string to be copied)
 * @dstn: This refers to the destination
 * Return: a pointer to the destination
 */

char *_strcpy(char *dstn, char *sc)
{
	int a = 0;

	if (dstn == sc || sc == 0) /* where destination is same as source */
		return (dstn);
	while (sc[a]) /* otherwise, copy each string from source to destination */
	{
		dstn[a] = sc[a];
		a++;
	}
	dstn[a] = 0; /* otherwise; destination is null, if source is null */

	return (dstn);
}

/**
 * _strchr - A funtion that locates a character in a string
 * @ch: Refers to the character to be searched for
 * @str: Refers to the string inwhich the character will be searched
 * Return: a pointer to the memory str; NULL if chraracter doesn't exist
 */

char *_strchr(char *str, char ch)
{
	while (*str != '\0') /* searches for the the character in the string */
		if (*str == ch) /* return the point to the str */
			return (str);
	return (NULL);
}


/**
 * *_strncpy - A function that copies n characters of a given string
 * @sc: Refers to the source string (to be copied)
 * @dstn: Refers to the destination string
 * @n: Refers to the number of characters in @sc to be copied
 * Return: the copied string
 */

char *_strncpy(char *dstn, char *sc, int n)
{
	int i;
	int j;
	char *str = dstn;

	i = 0;
	while (sc[i] != '\0' && i < n - 1)
	{
		dstn[i] = sc[i];
		i++;
	}
	if (i < n) /* Have gotten to the  end of the source string */
	{
		j = i;
		while (j < n) /* Copy the null character until n is reached */
		{
			dstn[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * *_strncat - A function that concatenateds n chars from one string to another
 * @sc: Refers to the source string
 * @dstn: Refers to the destination string
 * @n: Refers to the number of characters to be concatenated
 * Return: The concatenated string.
 */

char *_strncat(char *dstn, char *sc, int n)
{
	int i;
	int j;
	char *str = dstn;

	i = 0;
	j = 0;
	while (dstn[i] != '\0')
		i++;
	while (sc[j] != '\0' && j < n) /* checks for the first string */
	{
		dstn[i] = sc[j]; /* Appends chracter to the destination str */
		i++;
		j++;
	}
	if (j < n) /* appends null char when all chars in sc have been copied */
		dstn[i] = '\0';
	return (str);
}



