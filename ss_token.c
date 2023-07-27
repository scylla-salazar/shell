#include "shell.h"

/**
 * **_strtok1 - A function that splits a str into words using delimeter
 * @delm: This refers to the delimeter;
 * @str: This refers to the string to be splitted
 * Return: NULL (on failure); or a ponter to an array of strings (On success)
 */

char **_strtok1(char *str, char delm)
{
	int i, j, k, n;
	char **a;
	int num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delm && str[i + 1] == delm) ||
		    (str[i] != delm && !str[i + 1]) || str[i + 1] == delm)
			num++;
	if (num == 0)
		return (NULL);
	a = malloc((1 + num) * sizeof(char *));
	if (!a)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (str[i] == delm && str[i] != delm)
			i++;
		k = 0;
		while (str[i + k] != delm && str[i + k] && str[i + k] != delm)
			k++;
		a[j] = malloc((k + 1) * sizeof(char));
		if (!a[j])
		{
			for (k = 0; k < j; k++)
				free(a[k]);
			free(a);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			a[j][n] = str[i++];
		a[j][n] = 0;
	}
	a[j] = NULL;
	return (a);
}


/**
 * **_strtok2 - A function splits a given str into words; repeat delim ignored
 * @delm: This refer to the delimeter
 * @str: This refers to thr given str.
 * Return: NULL (On failure); a pointer to an array of strings (On success).
 */

char **_strtok2(char *str, char *delm)
{
	int i, j, k, n;
	char **a;
	int num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delm)
		delm = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delm) && (is_delim(str[i + 1], delm) ||
					!str[i + 1]))
			num++;


	if (num == 0)
		return (NULL);
	a = malloc((1 + num) * sizeof(char *));
	if (!a)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_delim(str[i], delm))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delm) && str[i + k])
			k++;
		a[j] = malloc((k + 1) * sizeof(char));
		if (!a[j])
		{
			for (k = 0; k < j; k++)
				free(a[k]);
			free(a);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			a[j][n] = str[i++];
		a[j][n] = 0;
	}
	a[j] = NULL;
	return (a);
}

