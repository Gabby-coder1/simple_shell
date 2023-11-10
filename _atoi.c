#include "shell.h"

/**
 * collective - Returning true if shell is collective mode
 * @info: Struct Address
 *
 * Return: 1 if collective mode, 0 otherwise
 */
int collective(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checking if character is a delimeter
 * @g: The character to check
 * @delim: The delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char g, char *delim)
{
	while (*delim)
		if (*delim++ == g)
			return (1);
	return (0);
}

/**
 *_isalpha - Checking for alphabetic character
 *@g: The character to input
 *Return: 1 if g is alphabetic, 0 otherwise
 */

int _isalpha(int g)
{
	if ((g >= 'a' && g <= 'z') || (g >= 'A' && g <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - Converting a string to an integer
 *@b: The string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *b)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  b[i] != '\0' && flag != 2; i++)
	{
		if (b[i] == '-')
			sign *= -1;

		if (b[i] >= '0' && b[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (b[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
