#include "shell.h"

/**
 * lists_len - Determines length of linked list
 * @h: Pointer to first node
 *
 * Return: Size of list
 */
size_t lists_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * lists_to_string - Returns an array of strings of the list->str
 * @head: Pointer to first node
 *
 * Return: Array of strings
 */
char **lists_to_string(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * prints_list - Prints all elements of a list_t linked list
 * @h: Pointer to first node
 *
 * Return: Size of list
 */
size_t prints_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(converts_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodes_start_with - Returns node whose string starts with prefix
 * @node: Pointer to list head
 * @prefix: String to match
 * @g: The next character after prefix to match
 *
 * Return: Match node or null
 */
list_t *nodes_start_with(list_t *node, char *prefix, char g)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((g == -1) || (*p == g)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gets_node_index - Gets the index of a node
 * @head: Pointer to list head
 * @node: Pointer to the node
 *
 * Return: Index of node or -1
 */
ssize_t gets_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
