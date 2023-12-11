#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <libk/stdio.h>
#include <libk/string.h>
#include <stdint.h>

int print_int(int32_t int_);
int print_uint(uint32_t int_);
int print_hex(uint32_t int_);
int print_char(char char_);

int printf(const char *restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0')
	{
		if (*format != '%')
		{
			int to_write = 0;
			while (*(format + to_write) != '%' && *(format + to_write) != '\0')
			{
				to_write++;
			}
			print(format, to_write);
			written += to_write;
			format += to_write;
		}
		else if (*(format + 1) == 'c')
		{
			format += 2;
			char c = (char)va_arg(parameters, int /* char promotes to int */);
			print_char(c);
			written++;
		}
		else if (*(format + 1) == 's')
		{
			format += 2;
		}
		else if (*(format + 1) == 'd')
		{
			format += 2;
			int32_t i = (int32_t)va_arg(parameters, int /* char promotes to int */);
			written += print_int(i);
		}
		else if (*(format + 1) == 'u')
		{
			format += 2;
			uint32_t i = (uint32_t)va_arg(parameters, unsigned int /* char promotes to int */);
			written += print_uint(i);
		}
		else if (*(format + 1) == 'x')
		{
			format += 2;
			uint32_t i = (uint32_t)va_arg(parameters, unsigned int /* char promotes to int */);
			written += print_hex(i);
		}
		else
		{
			format++;
		}
	}

	va_end(parameters);
	return written;
}

#define BUF_SIZE 30

int print_int(int32_t int_)
{
	char buf[BUF_SIZE];
	buf[BUF_SIZE - 1] = 0;
	int neg = (int_ >= 0) ? 0 : 1;
	int written = 0;
	while (int_ != 0)
	{
		written++;
		buf[BUF_SIZE - 1 - written] = (int_ % 10) + '0';
		int_ /= 10;
	}
	if (neg)
	{
		written++;
		buf[BUF_SIZE - 1 - written] = '-';
	}
	print(&(buf[BUF_SIZE - 1 - written]), written + 1);
	return written;
}

int print_uint(uint32_t int_)
{
	char buf[BUF_SIZE];
	buf[BUF_SIZE - 1] = 0;
	int written = 0;
	while (int_ != 0)
	{
		written++;
		buf[BUF_SIZE - 1 - written] = (int_ % 10) + '0';
		int_ /= 10;
	}
	print(&(buf[BUF_SIZE - 1 - written]), written + 1);
	return written;
}

int print_hex(uint32_t int_)
{
	char buf[BUF_SIZE];
	buf[BUF_SIZE - 1] = 0;
	int written = 0;
	while (int_ != 0)
	{
		written++;
		int mod = int_ % 16;
		buf[BUF_SIZE - 1 - written] = (mod < 10) ? mod + '0' : mod - 10 + 'A';
		int_ /= 16;
	}
	print(&(buf[BUF_SIZE - 1 - written]), written + 1);
	return written;
}

int print_char(char char_)
{
	print(&char_, 1);
	return 1;
}