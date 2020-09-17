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

/**
 * @brief Divide between two unsigned long integers.
 *
 * @param a First operand.
 * @param b Second operand.
 *
 * Source: https://github.com/gcc-mirror/gcc/blob/master/libgcc/udivmodsi4.c
 *
 * @returns The result of @p a divide by @p b.
 */
unsigned long __udivmodsi4(unsigned long num, unsigned long den, int modwanted)
{
	unsigned long bit = 1;
	unsigned long res = 0;

	while (den < num && bit && !(den & (1L << 31)))
	{
		den <<= 1;
		bit <<= 1;
	}

	while (bit)
	{
		if (num >= den)
		{
			num -= den;
			res |= bit;
		}

		bit >>= 1;
		den >>= 1;
	}

	if (modwanted)
		return num;

	return res;
}

