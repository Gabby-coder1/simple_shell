#include "shell.h"

/**
 * _atenv - Prints the current environment
 * @info: Structure contains potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _atenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _butenv - Gets the value of an environ variable
 * @info: Structure contains potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: The value
 */
char *_butenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _atsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure contains potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _atsetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _atunsetenv - Remove an environment variable
 * @info: Structure contains potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _atunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * inhabit_env_list - populates env linked list
 * @info: Structure contains potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int inhabit_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
