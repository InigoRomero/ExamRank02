#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

size_t ft_strlen(char *s)
{
	size_t i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_numlen(long long n, int base_len)
{
	int i = 1;
	while (n >= base_len || n <= -base_len)
	{
		n = n / base_len;
		i++;
	}
	return (i);
}

void	ft_putnum(long long n, int base_len, char *base)
{
	if (n >= base_len)
		ft_putnum(n / base_len, base_len, base);
	write (1, &base[n % base_len], 1);
}

int ft_printf(const char *format, ...)
{
	va_list valist;
	long long n;
	char *string, *str, *base;
	int zeros = 0, spaces = 0, width = 0,  prec = 0, bolprec = 0, neg = 0, x = 0, leng = 0, base_len;
	va_start(valist, format);
	str = (char *)format;
	while (*str)
	{
		if (*str == '%')
		{
			zeros = 0, spaces = 0, width = 0,  prec = 0, bolprec = 0, neg = 0, x = 0;
			str++;
			while (*str <= '9' && *str >= '0')
			{
				width = width * 10 + (*str - 48);
				str++;
			}
			if (*str == '.')
			{
				str++;
				while (*str <= '9' && *str >= '0')
				{
					prec = prec * 10 + (*str - 48);
					str++;
				}
				bolprec = 1;
			}
			if (*str == 's')
			{
				string = va_arg(valist, char*);
				if (!string)
					string = "(null)";
				x = (int)ft_strlen(string);
			}
			if (*str == 'd')
			{
				n = va_arg(valist, int);
				if (n < 0)
				{
					n = n *-1;
					neg = 1;
				}
				base = "0123456789";
				base_len = 10;
				x = ft_numlen(n, base_len) + neg;
			}
			if (*str == 'x')
			{
				n = va_arg(valist, unsigned);
				base = "0123456789abcdef";
				base_len = 16;
				x = ft_numlen(n, base_len);
			}
			if (bolprec == 1 && prec > x && *str == 's')
				spaces = prec - x;
			else if (bolprec == 1 && prec > x && *str != 's')
				zeros = prec - x +  neg;
			else if (bolprec == 1 && prec < x && *str == 's')
				x = prec;
			else if (bolprec == 1 && prec == 0 && (*str == 's' || n == 0))
				x = 0;
			spaces = width -  x - zeros;
			while (spaces-- > 0)
			{
				write (1, " ", 1);
				leng++;
			}
			if (neg == 1)
				write (1, "-", 1);
			while (zeros-- > 0)
			{
				write (1, "0", 1);
				leng++;
			}
			if (*str == 's')
				write (1, string, x);
			else if (x > 0)
				ft_putnum(n, base_len, base);
			leng += x;
			str++;
		}
		else
		{
			write (1, str, 1);
			leng++;
			str++;
		}
	}
	return (leng);
}

int main ()
{
	printf("holabb %20.3s %10s %.10s %.5d %.0d %10.10d  %10.10d %.5x %.0x %10.10x %10.10x\n", "jaime", "pepeito", "jojojojojojojo", 3, 0, 30, -30, 3, 0 , 30, -30);
	ft_printf("holabb %20.3s %10s %.10s %.5d %.0d %10.10d  %10.10d %.5x %.0x %10.10x %10.10x\n", "jaime", "pepeito", "jojojojojojojo", 3, 0, 30,-30, 3, 0 , 30, -30);
}