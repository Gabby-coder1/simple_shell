#include "shell.h"

/**
 * is_chain - Test the current char in buffer is a chain delimeter
 * @info: The parameter struct
 * @buf: The char buffer
 * @q: Address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *q)
{
	size_t j = *q;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = j;
	return (1);
}

/**
 * checks_chain - Checks whether to continue chaining based on last status
 * @info: The parameter struct
 * @buf: The char buffer
 * @q: Address of current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void checks_chain(info_t *info, char *buf, size_t *q, size_t i, size_t len)
{
	size_t j = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*q = j;
}

/**
 * replaces_alias - Replaces an aliases in a tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_alias(info_t *info)
{
	int i;
	list_t *node;
	char *q;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strgchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replaces_vars - Replaces vars in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(converts_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(converts_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replaces_string - Replaces string
 * @old: Address of old string
 * @new: A new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
