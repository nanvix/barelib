/*
 * MIT License
 *
 * Copyright(c) 2011-2020 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <posix/stdarg.h>
#include <posix/stddef.h>

#ifndef __qemu_riscv32__
typedef unsigned long long UNSIGNED_T;
#else
typedef unsigned UNSIGNED_T;
#endif

/**
 * @brief Converts an integer to a string.
 *
 * @param str  Output string.
 * @param num  Number to be converted.
 * @param base Base to use.
 *
 * @returns The length of the output string.
 */
static int itoa(char *str, unsigned num, int base)
{
	char *b = str;
	char *p, *p1, *p2;
	unsigned divisor;

#if (__HAS_HW_DIVISION)

	divisor = 10;

	if (base == 'x')
	{
		*b++ = '0'; *b++ = 'x';
		divisor = 16;
	}

	p = b;

	/* Convert number. */
	do
	{
		unsigned remainder;

#ifdef __GLIBC_BUG__
		remainder = (divisor == 10 ? (num % 10) : (num % 16));
#else
		remainder = num % divisor;
#endif

		*p++ = (remainder < 10) ?
			remainder + '0' : remainder + 'a' - 10;

#ifdef __GLIBC_BUG__
	} while ((divisor == 10 ? (num /= 10) : (num /= 16)));
#else
	} while (num /= divisor);
#endif

#else

	((void) base);

	*b++ = '0'; *b++ = 'x';
	divisor = 16;

	p = b;

	/* Convert number. */
	do
	{
		unsigned remainder = num & 0xf;

		*p++ = (remainder < 10) ?
			remainder + '0' : remainder + 'a' - 10;
	} while ((num  = (num >> 4)));

#endif

	/* Fill up with zeros. */
	if (divisor == 16)
	{
		while ((p - b) < 8)
			*p++ = '0';
	}

	/* Reverse BUF. */
	p1 = b; p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1++ = *p2;
		*p2-- = tmp;
	}

	return(p - str);
}

#ifndef __qemu_riscv32__

/**
 * @brief Converts an 64 bit integer to a string.
 *
 * @param str  Output string.
 * @param num  Number to be converted.
 * @param base Base to use.
 *
 * @returns The length of the output string.
 */
static int itoa64(char *str, UNSIGNED_T num, int base)
{
	char *b = str;
	char *p, *p1, *p2;
	unsigned divisor;

#if (__HAS_HW_DIVISION)

	divisor = 10;

	if (base == 'h')
	{
		divisor = 16;
		*b++ = '0';
		*b++ = 'x';
	}

	p = b;

	/* Convert number. */
	do
	{
		UNSIGNED_T remainder;

#ifdef __GLIBC_BUG__
		remainder = (divisor == 10 ? (num % 10) : (num % 16));
#else
		remainder = num % divisor;
#endif

		*p++ = (remainder < 10) ?
			remainder + '0' : remainder + 'a' - 10;

#ifdef __GLIBC_BUG__
	} while ((divisor == 10 ? (num /= 10) : (num /= 16)));
#else
	} while (num /= divisor);
#endif

#else

	((void) base);

	divisor = 16;
	*b++ = '0'; *b++ = 'x';

	/* Convert number. */
	do
	{
		UNSIGNED_T remainder = num & 0xf;

		*p++ = (remainder < 10) ?
			remainder + '0' : remainder + 'a' - 10;
	} while ((num  = (num >> 4)));

#endif


	/* Fill up with zeros. */
	if (divisor == 16)
	{
		while ((p - b) < 16)
			*p++ = '0';
	}

	/* Reverse BUF. */
	p1 = b; p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1++ = *p2;
		*p2-- = tmp;
	}

	return(p - str);
}

#endif /* !qemu_riscv32 */

 /**
 * @brief Count number of digits a number has.
 *
 * @param num Number to have digits counted.
 *
 * @returns Number of digits of num.
 */
static unsigned count_digits(UNSIGNED_T num)
{
	unsigned digits = 0;
	while (num != 0)
	{
#if (__HAS_HW_DIVISION)
		num /= 10;
#else
		UNSIGNED_T quocient = 0;
		UNSIGNED_T dividend = num;
		while (dividend >= 10)
		{
			dividend -= 10;
			quocient++;
		}

		num = quocient;
#endif
		++digits;
	}

	return digits;
}

/**
 * @brief Writes at most size bytes (including the terminating null byte ('\0'))
 * of formatted data to str. If the the result is larger than size, the output
 * string will be truncated. If a number needs to be truncated, not even the
 * part that fits in the output will be written, so no number will be in the output.
 *
 * @param str	Output string.
 * @param size	Write at most size bytes (including null byte).
 * @param fmt	Formatted string.
 * @param args	Variable arguments list.
 *
 * @returns Length of output string (excluding terminating null byte). If size is 0
 *  or fmt string is NULL or empty, the function returns -1.
 *
 * @todo TODO: Should return the length the string would have had if it wasn't truncated.
 */
int __vsnprintf(char *str, size_t size, const char *fmt, va_list args)
{
	char *base = str;
	char *s;
	UNSIGNED_T number;

	if (size == 0 || fmt == NULL)
		return (-1);

	/* Format string. */
	while (*fmt != '\0' && (size_t)(str - base) < (size - 1))
	{
		/* No conversion needed. */
		if (*fmt != '%')
			*str++ = *fmt;
		else
		{
			switch (*(++fmt))
			{
				/* Character. */
				case 'c':
					*str++ = (char)va_arg(args, int);
					break;
				/* Number. */
				case 'd':
					number = va_arg(args, unsigned);
					if ((size_t)(count_digits(number) + (str - base)) <= (size - 1))
						str += itoa(str, number, *fmt);
					break;
				case 'x':
					/* Hex numbers are currently being converted
					 * using always 0x + 8 digits. */
					if ((size_t)(10 + (str - base)) <= (size - 1))
						str += itoa(str, va_arg(args, unsigned), *fmt);
					break;
#ifndef __qemu_riscv32__
				case 'l':
					if(*(fmt + 1) == 'x')
					{
						/* Long hex numbers are currently being converted
						 * using always 0x + 16 digits. */
						if ((size_t)(18 + (str - base)) <= (size - 1))
							str += itoa64(str, va_arg(args, UNSIGNED_T), 'h');
						++fmt;
					}
					else
					{
						number = va_arg(args, UNSIGNED_T);
						if ((size_t)(count_digits(number) + (str - base)) <= (size - 1))
							str += itoa64(str, number, 'l');
					}
					break;
#endif
				/* String. */
				case 's':
					s = va_arg(args, char*);
					while (*s != '\0' && (size_t)(str - base) < (size - 1))
						*str++ = *s++;
					break;
				/* Ignore. */
				default:
					break;
			}
		}

		++fmt;
	}

	*str = '\0';

	return ((str - base) - 1);
}
