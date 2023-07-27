#include "shell.h"

/**
 * main - This is entry point
 * @ac: this REFERS TO arg count;
 * @av: refers to the arg vector
 * Return: 0 on succes; or 1 if error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2) /*  */
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1) /*  */
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eput(av[0]);
				_eput(": 0: Can't open ");
				_eput(av[1]);
				eputchar('\n');
				eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	_populate_envlist(info);
	_read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
