#include "shell.h"

/**
 **_strngcpy - Copies a string
 *@dest: The destination string to be copied to
 *@src: The source string
 *@n: The amount of characters to be copied
 *Return: The concatenated string
 */
char *_strngcpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strngcat -Concatenates two strings
 *@dest: The first string
 *@src: The second string
 *@n: The amount of bytes to be maximally used
 *Return: The concatenated string
 */
char *_strngcat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strgchr - Locates a character in a string
 *@t: The string to be parsed
 *@c: The character to look for
 *Return: (t) a pointer to the memory area s
 */
char *_strgchr(char *t, char c)
{
	do {
		if (*t == c)
			return (t);
	} while (*t++ != '\0');

	return (NULL);
}
