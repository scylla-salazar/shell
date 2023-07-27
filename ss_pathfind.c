#include "shell.h"

/**
 * find_path - A funtion that finds a cmd in the PATH string,
 * @pathstrn: This is the PATH str
 * @cmd: This is the cmd to be found
 * @info: This refers to the parametre struct
 * Return: NULL, or full cmd path (if found)
 */

char *find_path(info_t *info, char *pathstrn, char *cmd)
{
	/* variable declaration */
	int current_pos = 0, x = 0;
	char *path;

	if (!pathstrn) /* checks for path string */
		return (NULL);
	if ((_strlen(cmd) > 2) && _starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrn[x] || pathstrn[x] == ':')
		{
			path = dup_chars(pathstrn, current_pos, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (is_cmd(info, path))
				return (path);
			if (!pathstrn[x])
				break;
			current_pos = x;
		}
		x++;
	}
	return (NULL);
}


/**
 * dup_chars - A function that duplicates characters'
 * @strt: This refers to the starting index
 * @stop: THis refers to the stopping index
 * @pathstrn: This refers to the PATH string''
 * Return: ptr to the new buffer.
 */

char *dup_chars(char *pathstrn, int strt, int stop)
{
	int p = 0, q = 0;
	static char buff[1024];

	for (q = 0, p = strt; p < stop; p++)
		if (pathstrn[p] != ':')
			buff[q++] = pathstrn[p];
	buff[q] = 0;
	return (buff);
}


/**
 * is_cmd - A funtion that checks if a file is an executable cmd
 * @path: This refers to the file path
 * @info: This refers to the info struct
 * Return: 1 (True), 0 (Otherwise)
 */


int is_cmd(info_t *info, char *path)
{
	struct stat st; /* variable declaration */

	(void)info;
	if (!path || stat(path, &st)) /* check if the file is executable */
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

