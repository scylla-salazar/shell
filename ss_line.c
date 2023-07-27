#include "shell.h"

/**
 * _sig_intHandler - A funtion that blocks ctrl-C
 * @sig_no: This refers to the signal number
 * Return: void;
 */

void _sig_intHandler(__attribute__((unused))int sig_no)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


/**
 * read_buf - A funtion that reads a buffer
 * @buff: This refers to the buffer
 * @s: This refers to the size
 * @info: This refers to the parameter struct
 * Return: size read, i.
 */

ssize_t read_buf(info_t *info, char *buff, size_t *s)
{
	ssize_t i = 0; /*initialize variable */

	if (*s)
		return (0);
	i = read(info->readfd, buff, READ_BUF_SIZE); /* reads the buffer size*/
	if (i >= 0)
		*s = i;
	return (i);
}


/**
 * get_input - A function that gets a line without the new line
 * @info: This refers to the parametre struct;
 * Return: no of bytes read.
 */

ssize_t get_input(info_t *info)
{
	static size_t u, v;
	ssize_t i = 0;
	static char *buff;
	static size_t leng;
	char *t, **buff_t = &(info->arg);

	_putchar(BUF_FLUSH);
	i = input_buf(info, &buff, &leng);
	if (i == -1) /* signifies End of File*/
		return (-1);
	if (leng) /* checks for commands left in the chain buff */
	{
		v = u;
		t = buff + u;

		check_chain(info, buff, &v, u, leng);
		while (v < leng)
		{
			if (is_chain(info, buff, &v))
				break;
			v++;
		}
		u = v + 1;
		if (u >= leng)
		{
			u = leng = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buff_t = t;
		return (_strlen(t));
	}

	*buff_t = buff;
	return (i);
}


/**
 * input_buf - A funtion that buffers chained cmds
 * @buff: This refers to the buffer addr
 * @leng: This refers to the length var addr
 * @info: This refers to the parametre struct;
 * Return: No of bytes read,
 */

ssize_t input_buf(info_t *info, char **buff, size_t *leng)
{
	size_t leng_t = 0;
	ssize_t u = 0;

	if (!*leng)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, _sig_intHandler);

#if USE_GETLINE
		u = getline(buff, &leng_t, stdin);
#else
		u = _getline(info, buff, &leng_t);
#endif
		if (u > 0)
		{
			if ((*buff)[u - 1] == '\n')
			{
				(*buff)[u - 1] = '\0';
				u--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			_build_historylist(info, *buff, info->histcount++);
			{
				*leng = u;
				info->cmd_buf = buff;
			}
		}
	}
	return (u);
}


/**
 * _getline - A funtion that gets the next line of input from standard input
 * @ptr: This refers to the addr of pointer to buffer
 * @leng: this refers to size of the preallocated pointer buffer, if not NULL
 * @info: This refer to the parametre struct
 * Return: size v.
 *
 */

int _getline(info_t *info, char **ptr, size_t *leng)
{
	static size_t x, len;
	static char buff[READ_BUF_SIZE];
	ssize_t u = 0, v = 0;
	size_t y;
	char *p = NULL, *z, *new_p = NULL;

	p = *ptr;
	if (p && leng)
		v = *leng;
	if (x == len)
		x = len = 0;

	u = read_buf(info, buff, &len);
	if (u == -1 || (u == 0 && len == 0))
		return (-1);

	z = _strchr(buff + x, '\n');
	y = z ? 1 + (unsigned int)(z - buff) : len;
	new_p = _realloc(p, v, v ? v + y : y + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (v)
		_strncat(new_p, buff + x, y - x);
	else
		_strncpy(new_p, buff + x, y - x + 1);

	v += y - x;
	x = y;
	p = new_p;

	if (leng)
		*leng = v;
	*ptr = p;
	return (v);
}

