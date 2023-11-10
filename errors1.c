#include "shell.h"

/**
 * _terratoi - Converts a string to an integer
 * @t: The string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _terratoi(char *t)
{
	int i = 0;
	unsigned long int result = 0;

	if (*t == '+')
		t++;  /* TODO: why does this make main return 255? */
	for (i = 0;  t[i] != '\0'; i++)
	{
		if (t[i] >= '0' && t[i] <= '9')
		{
			result *= 10;
			result += (t[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * prints_error - Prints an error message
 * @info: The parameter & return info struct
 * @estr: String contains specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void prints_error(info_t *info, char *estr)
{
	_puts(info->fname);
	_puts(": ");
	print_d(info->line_count, STDERR_FILENO);
	_puts(": ");
	_puts(info->argv[0]);
	_puts(": ");
	_puts(estr);
}

/**
 * print_d - Function prints a decimal (integer) number (base 10)
 * @input: The input
 * @fd: The filedescriptor to write to
 *
 * Return: Number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * converts_number - Converter function, a clone of itoa
 * @num: Number
 * @base: Base
 * @flags: Argument flags
 *
 * Return: String
 */
char *converts_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removes_comment - Function replaces first instance of '#' with '\0'
 * @buf: Address of the string to modify
 *
 * Return: Always 0;
 */
void removes_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
