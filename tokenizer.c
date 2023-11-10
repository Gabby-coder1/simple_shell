#include "shell.h"

/**
 * **strtow - Splits a string to words. Repeated delimiters are ignored
 * @str: The input string
 * @y: The delimeter string
 * Return: Pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *y)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!y)
		y = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], y) && (is_delim(str[i + 1], y) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], y))
			i++;
		k = 0;
		while (!is_delim(str[i + k], y) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - Splits string to words
 * @str: The input string
 * @y: The delimeter
 * Return: Pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char y)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != y && str[i + 1] == y) ||
		    (str[i] != y && !str[i + 1]) || str[i + 1] == y)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == y && str[i] != y)
			i++;
		k = 0;
		while (str[i + k] != y && str[i + k] && str[i + k] != y)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
