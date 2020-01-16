#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

size_t ft_strlen(char *s)
{
	size_t i = 0;
	while (s[i]!= '\0')
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

int	ft_printf(char *format, ...)
{
	va_list valist;
	char *base, *s, *str;
	long num;
	int prec = 0, width = 0, leng = 0, n = 0, space = 0, zeros = 0, base_len, bolprec = 0, neg = 0;
	va_start(valist, format);
	str = (char *)format;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			prec = 0, width = 0, n = 0, space = 0, zeros = 0, bolprec = 0, neg = 0;
			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + (*str - 48);
				str++;
			}
			if (*str == '.')
			{
				str++;
				while (*str >= '0' && *str <= '9')
				{
					prec = prec * 10 + (*str - 48);
					str++;
				}
				bolprec = 1;
			}
			if (*str == 's')
			{
				s = va_arg(valist, char *);
				if (!s)
					s = "(null)";
				n = ft_strlen(s);
			}
			if (*str == 'x')
			{
				num = va_arg(valist, unsigned);
				base = "0123456789abcdef";
				base_len = 16;
				n = ft_numlen(num, base_len);
			}
			if (*str == 'd')
			{
				num = va_arg(valist, int);
				base = "0123456789";
				base_len = 10;
				if (num < 0)
				{
					num = num * -1;
					neg = 1;
				}
				n = ft_numlen(num, base_len) + neg;
			}
			if (bolprec == 1 && prec > n && *str != 's')
				zeros = prec - n + neg;
			else if (bolprec == 1 && prec < n && *str == 's')
				n = prec;
			else if (bolprec == 1 && prec == 0 && (*str == 's'|| num == 0))
				n = 0;
			space = width - n - zeros;
			while (space-- > 0)
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
				write(1, s, n);
			else if (n > 0)
				ft_putnum(num, base_len, base);
			leng += n;
			str++;
		}
		else
		{
			write (1, str, 1);
			str++;
			leng++;
		}
	}
	return (leng);
}

/*int main()
{
	printf("jaja%30.10s %.3s %.30s %20s %30.10d %30d %.10d %30.10d %5.0d %30.10x %30x %.10x %30.10x %5.0x\n", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030, 0, 30, 30 , 303030, -303030, 0);
	ft_printf("jaja%30.10s %.3s %.30s %20s %30.10d %30d %.10d %30.10d %5.0d %30.10x %30x %.10x %30.10x %5.0x\n", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030, 0, 30, 30 , 303030, -303030, 0);

	printf("\n%6.30s\n", "jaime");
	ft_printf("\n%6.30s", "jaime");
}*/
