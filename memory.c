#include "shell.h"

/**
 * bfrees - Frees a pointer and NULLs the address
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfrees(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
