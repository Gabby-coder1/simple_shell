#include "shell.h"

/**
 * hshs - Main shell loop
 * @info: The parameter & return info struct
 * @av: The argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hshs(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clears_info(info);
		if (collective(info))
			_puts("$ ");
		_putchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			sets_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (collective(info))
			_putchar('\n');
		frees_info(info, 0);
	}
	writes_history(info);
	frees_info(info, 1);
	if (!collective(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * finds_builtin - Finds builtin command
 * @info: The parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int finds_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _atexit},
		{"env", _atenv},
		{"help", _athelp},
		{"history", _athistory},
		{"setenv", _atsetenv},
		{"unsetenv", _atunsetenv},
		{"cd", _atcd},
		{"alias", _atalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * finds_cmd - Finds a command in PATH
 * @info: The parameter and return info struct
 *
 * Return: Void
 */
void finds_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _butenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((collective(info) || _butenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * forks_cmd - Forks a an exec thread to run cmd
 * @info: The parameter and return info struct
 *
 * Return: Void
 */
void forks_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, gets_environ(info)) == -1)
		{
			frees_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
