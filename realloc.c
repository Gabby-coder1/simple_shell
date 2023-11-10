#include "shell.h"

/**
 **_memsets - Fills memory with a constant byte
 *@b: The pointer to the memory area
 *@m: The byte to fill *s with
 *@n: The amount of bytes to be filled
 *Return: (b) a pointer to the memory area s
 */
char *_memsets(char *b, char m, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		b[i] = m;
	return (b);
}

/**
 * ffrees - Frees a string of strings
 * @pp: String of strings
 */
void ffrees(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _reallocs - Reallocates a block of memory
 * @ptr: Pointer to previous malloc'ated block
 * @old_size: Byte size of previous block
 * @new_size: Byte size of new block
 *
 * Return: Pointer to da ol'block nameen.
 */
void *_reallocs(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
