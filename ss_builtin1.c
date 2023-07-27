#include "shell.h"


/**
 * _myhelp - A funtion that changes the current dir of a process
 * @info: This refers to the struct, which contains the potential arguments
 * Return: 0 (Always)
 */

int _myhelp(info_t *info)
{
	char **arg_arrays;

	arg_arrays = info->argv;
	_puts("help call works. Function not implemented yet \n");
	if (0)
		_puts(*arg_arrays);
	return (0);
}


/**
 * _myexit - A funtion that exits the shell
 * @info: This refers to the struct, which contains the potential args
 * Return: exits with a exit status, (-2) if otherwise
 */

int _myexit(info_t *info)
{
	int exit_checker;

	if (info->argv[1])
	{
		exit_checker = _erratoi(info->argv[1]);
		if (exit_checker == -1)
		{
			info->status = 2;
			print_error(info, "Illegal num: ");
			_eput(info->argv[1]);
			eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}


/**
 * _mycd - A funtion that changes the current directory of the process
 * @info: This Refers to the structure, containing potential arguments
 *  Return: Always, 0
 */


int _mycd(info_t *info)
{
	char *ch, *dir, buff[1024];
	int chdir_ret;

	ch = getcwd(buff, 1024);
	if (!ch)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ch);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "cannot cd to ");
		_eput(info->argv[1]), eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}


