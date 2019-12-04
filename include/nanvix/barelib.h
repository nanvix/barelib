/*
 * MIT License
 *
 * Copyright(c) 2011-2019 The Maintainers of Nanvix
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

/**
 * @defgroup barelib Bare Library
 * @ingroup kernel
 */

#ifndef NANVIX_BARELIB_H_
#define NANVIX_BARELIB_H_

	#include <posix/stddef.h>
	#include <posix/stdarg.h>

/*============================================================================*
 * Memory Manipulation                                                        *
 *============================================================================*/

/**
 * @addtogroup barelib-memory
 * @ingroup barelib
 */
/**@{*/

	/**
	 * @brief Finds a byte in memory.
	 *
	 * @param s Target memory area.
	 * @param n Number of bytes to analyze.
	 *
	 * @returns A pointer to the located byte, or a null pointer if
	 * the byte does not occur in the object.
	 */
	extern void *__memchr(const void *s, int c, size_t n);

	/**
	 * @brief Compares bytes in memory.
	 *
	 * @param s1 Target memory area one.
	 * @param s2 Target memory area two.
	 *
	 * @returns Zero if the memory areas are equal, and non-zero
	 * otherwise.
	 */
	extern int __memcmp(const void *s1, const void *s2, size_t n);

	/**
	 * @brief Copy bytes in memory.
	 *
	 * @param s1 Target memory area.
	 * @param s2 Source memory area.
	 * @param n  Number of bytes to be copied.
	 *
	 * @returns A pointer to the target memory area.
	 */
	extern void *__memcpy(void *s1, const void *s2, size_t n);

	/**
	 * @brief Copies bytes in memory with overlapping areas.
	 *
	 * @param s1 Target memory area.
	 * @param s2 Source memory area.
	 * @param n  Number of bytes to be copied.
	 *
	 * @returns A pointer to the target memory area.
	 */
	extern void *__memmove(void *s1, const void *s2, size_t n);

	/**
	 * @brief Sets bytes in memory.
	 *
	 * @param s Pointer to target memory area.
	 * @param c Character to use.
	 * @param n Number of bytes to be set.
	 *
	 * @returns A pointer to the target memory area.
	 */
	extern void *__memset(void *s, int c, size_t n);

/**@}*/

/*============================================================================*
 * String Manipulation                                                        *
 *============================================================================*/

/**
 * @addtogroup barelib-string String Manipulation
 * @ingroup barelib
 */
/**@{*/

	/**
	 * @brief Concatenates two strings.
	 *
	 * @param s1 Pointer to target string.
	 * @param s2 Pointer to source string.
	 *
	 * @returns @p s1 is returned.
	 */
	extern char *__strcat(char *s1, const char *s2);

	/**
	 * @brief String scanning operation.
	 *
	 * @param s Target string.
	 * @param c target character.
	 *
	 * @returns A pointer to the byte, or a null pointer if the byte
	 * was not found.
	 */
	extern char *__strchr(const char *s, int c);

	/**
	 * @brief Compares two strings.
	 *
	 * @param s1 String one.
	 * @param s2 String two.
	 *
	 * @returns Zero if the strings are equal, and non-zero otherwise.
	 */
	extern int __strcmp(const char *s1, const char *s2);

	/**
	 * @brief Copies a string.
	 *
	 * @param s1 Target string.
	 * @param s2 Source string.
	 *
	 * @returns A pointer to the target string.
	 *
	 * @warning This function does not handle cache coherency.
	 */
	extern char *__strcpy(char *s1, const char *s2);

	/**
	 * @brief Get the length of a complementary substring.
	 *
	 * @param s1 Target string.
	 * @param s2 Source string.
	 *
	 * @returns The length of the computed segment of the string
	 * pointed to by s1; no return value is reserved to indicate an
	 * error.
	 */
	extern size_t __strcspn(const char *s1, const char *s2);

	/**
	 * @brief Returns the length of a string.
	 *
	 * @param str String to be evaluated.
	 *
	 * @returns The length of the string.
	 */
	extern size_t __strlen(const char *str);

	/**
	 * @brief Concatenates a string with part of another.
	 *
	 * @param s1 Pointer to target string.
	 * @param s2 Pointer to source string.
	 *
	 * @returns A pointer to @p s1.
	 */
	extern char *__strncat(char *s1, const char *s2, size_t n);

	/**
	 * @brief Compares part of two strings.
	 *
	 * @param s1 String one.
	 * @param s2 String two.
	 * @param n  Number of characters to be compared.
	 *
	 * @returns Zero if the strings are equal, and non-zero otherwise.
	 */
	extern int __strncmp(const char *s1, const char *s2, size_t n);

	/**
	 * @brief Copies part of a string.
	 *
	 * @param s1 Target string.
	 * @param s2 Source string.
	 * @param n  Number of characters to be copied.
	 *
	 * @returns A pointer to the target string.
	 *
	 * @warning This function does not handle cache coherency.
	 */
	extern char *__strncpy(char *s1, const char *s2, size_t n);

	/**
	 * @brief Gets length of fixed size string.
	 *
	 * @param s      Target string.
	 * @param maxlen Size of string.
	 *
	 * @returns The length of @p s.
	 */
	extern size_t __strnlen(const char *s, size_t maxlen);

	/**
	 * @brief Scans a string for a byte.
	 *
	 * @param s1 Target string.
	 * @param s2 Characters to look for.
	 *
	 * @returns A pointer to the byte or a null pointer if no byte
	 * from @p s2 occurs in @p s1.
	 */
	extern char *__strpbrk(const char *s1, const char *s2);

	/**
	 * @brief String scanning operation.
	 *
	 * @param s Target string.
	 * @param c target characeter.
	 *
	 * @returns A pointer to the byte or a null pointer if @p c does
	 * not occur in the string.
	 */
	extern char *__strrchr(const char *s, int c);

	/**
	 * @brief Gets length of a substring.
	 *
	 * @param s1 Target string.
	 * @param s2 Target substring.
	 *
	 * @param The computed length; no return value is reserved to
	 * indicate an error.
	 */
	extern size_t __strspn(const char *s1, const char *s2);

	/**
	 * @brief Finds a substring.
	 *
	 * @param s1 Target source string.
	 * @param s2 target substring.
	 *
	 * @returns A pointer to the located string or a null pointer if
	 * the string is not found. If @p s2 points to a string with zero
	 * length, the function shall return @p s1.
	 */
	extern char *__strstr(const char *s1, const char *s2);

/**@}*/

/*============================================================================*
 * String Formatting                                                          *
 *============================================================================*/

/**
 * @addtogroup barelib-formatting String Formatting
 * @ingroup barelib
 */
/**@{*/

	/**
	 * @brief Formats a string of a stdarg argument list.
	 *
	 * @param str  Target string.
	 * @param fmt  Formatted string.
	 * @param args Variable arguments list.
	 *
	 * @returns The number of characters written to the target string.
	 */
	extern int __vsprintf(char *str, const char *fmt, va_list args);

	/**
	 * @brief Formats a string.
	 *
	 * @param str Target string.
	 * @param fmt Formatted string.
	 *
	 * @returns The number of characters written to the target string.
	 */
	extern int __sprintf(char *str, const char *fmt, ...);

/**@}*/

/*============================================================================*
 * Miscellaneous                                                              *
 *============================================================================*/

/**
 * @addtogroup barelib-misc Miscellaneous
 * @ingroup barelib
 */
/**@{*/

	/**
	 * @brief Multiplies two integers.
	 *
	 * @param a First operand.
	 * @param b Second operand.
	 *
	 * @returns The result of @p a times @p b.
	 */
	extern int __mult(int a, int b);

/**@}*/

#endif /* NANVIX_BARELIB_H_ */
