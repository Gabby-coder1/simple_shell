#include "shell.h"

/**
 * main - Entry point
 * @ac: Arg count
 * @av: Arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts(av[0]);
				_puts(": 0: Can't open ");
				_puts(av[1]);
				_putchar('\n');
				_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	inhabit_env_list(info);
	reads_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
