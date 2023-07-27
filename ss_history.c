#include "shell.h"

/**
 * *_get_historyfile - A funtion that gets the history file
 * @info: This refers to the parametre struct.
 * Return: Allocated string containing the history filr;
 */

char *_get_historyfile(info_t *info)
{
	char *buff;
	char *dirs;

	dirs = _getenv(info, "HOME=");
	if (!dirs)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirs) + _strlen(HIST_FILE) + 2));

	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirs); /* Appends the history of the file */
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}


/**
 * _write_history - A function that creates a file, or append to an existin fil
 * @info: This refers to parametre struct
 * Return: 1 (if success); -1 (if failure)
 */

int _write_history(info_t *info)
{
	char *filenom = _get_historyfile(info);
	ssize_t fldir;
	list_t *node = NULL;


	if (!filenom) /* checks filename */
		return (-1);
	fldir = open(filenom, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenom);

	if (fldir == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fldir);
		_putfd('\n', fldir);
	}

	_putfd(BUF_FLUSH, fldir);
	close(fldir);
	return (1);
}


/**
 * renumber_history - a funtion that renumber d history linked list after chang
 * @info: This refers to the struct which contain possible arguments
 * Return: new histcount
 */


int renumber_history(info_t *info)
{
	int p;
	list_t *node = info->history;

	p = 0;

	while (node)
	{
		node->num = p++;
		node = node->next;
	}
	return (info->histcount = p); /* Renumbers the hidtory linked list */
}


/**
 * _build_historylist - A funtion that adds enty to a history linked lidt
 * @buff: This refers to the buffer;
 * @linecount: This Refers to the history linecount
 * @info: This refers to the structure contsining possible arguments'
 * Return: 0 (Always)
 */

int _build_historylist(info_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}


/**
 * _read_history - A function that reads the history from file.
 * @info: This refers to the parammetre struct
 * Return: histcount (on success), 0 (if otherwise)
 */

int _read_history(info_t *info)
{
	ssize_t fildir, readlen;
	int i;
	int lasts = 0, linecount = 0;
	ssize_t filsize = 0;
	struct stat str;
	char *buff = NULL, *filenom = _get_historyfile(info);

	if (!filenom) /* checks filename */
		return (0);
	fildir = open(filenom, O_RDONLY);
	free(filenom);
	if (fildir == -1) /* Checking the fildir */
		return (0);
	if (!fstat(fildir, &str))
		filsize = str.st_size;
	if (filsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (filsize + 1));
	if (!buff)
		return (0);
	readlen = read(fildir, buff, filsize);
	buff[filsize] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(fildir);
	for (i = 0; i < filsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			_build_historylist(info, buff + lasts, linecount++);
			lasts = i + 1;
		}
	if (lasts != i)
		_build_historylist(info, buff + lasts, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}



