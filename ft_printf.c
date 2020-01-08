#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
/* 

- It will manage only the following conversions: s,d and x
- It will manage the minimum field width. (we will never test with a field with of 0)
- It will manage only the precison flag `.`.
*/

size_t	ft_strlen(const char *s)
{
	size_t	value;
	int		i;

	i = 0;
	value = 0;
	while (s[i] != '\0')
	{
		i++;
		value++;
	}
	return (value);
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

static int		longofnum(long int n)
{
	int leng;

	leng = 0;
	if (n < 0)
	{
		leng++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		leng++;
	}
	return (leng);
}

static char		*inttochar(long int n, char *num, int leng)
{
	num[leng--] = '\0';
	if (n == 0)
		num[0] = 48;
	if (n < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		num[leng--] = 48 + (n % 10);
		n = n / 10;
	}
	return (num);
}

char			*ft_itoa(int n)
{
	char	*num;
	int		leng;

	leng = longofnum((long int)n);
	if (!n)
		leng = 1;
	if (!(num = (char *)malloc(sizeof(char) * (leng + 1))))
		return (NULL);
	return (num = inttochar((long int)n, num, leng));
}

static int		longofnumhex(long int n)
{
	int leng;

	leng = 0;
	if (n < 0)
	{
		leng++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 16;
		leng++;
	}
	return (leng);
}

static char		*inttocharhex(long int n, char *num, int leng)
{
	num[leng--] = '\0';
	if (n == 0)
		num[0] = 48;
	if (n < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		if (n % 16 <= 9)
			num[leng--] = 48 + (n % 16);
		else
			num[leng--] = 'W' + (n % 16);
		n = n / 16;
	}
	return (num);
}

char	*ft_strdup(const char *src)
{
	int i = 0;
	char *dest;

	if (!(dest = malloc(1 * ft_strlen(src))))
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	size;
	char	*tab;

	count = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	if (!(tab = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (count < len)
	{
		tab[count] = s[start + count];
		count++;
	}
	tab[count] = '\0';
	return (tab);
}

char			*ft_itoahex(long n)
{
	char	*num;
	int		leng;

	leng = longofnumhex((long int)n);
	if (!n)
		leng = 1;
	if (!(num = (char *)malloc(sizeof(char) * (leng + 1))))
		return (NULL);
	return (num = inttocharhex((long int)n, num, leng));
}

int ft_printf(const char *str, ... )
{
	va_list	valist;
	int n = 0;
	char *string;
	int d;
	unsigned int x;
	int prec = 0;
	int width = 0;
	int bolprec = 0;
	int bols = 0;
	int aux = 0;
	int	bolw = 0;
	int auxd = 0;
	if (!str)
		return (0);
	va_start(valist, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			while (*str <= '9' && *str >= '0')
			{
				width = width * 10 + (*str - 48);
				str++;
				bolw = 1;
			}
			if (*str == '.')
			{
				str++;
				while ((*str <= '9' && *str >= '0'))
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
					string = ft_strdup("(null)");
				bols = 1;
			}
			else if (*str == 'd')
			{
				d = va_arg(valist, int);
				string = ft_itoa(d);
			}
			else if (*str == 'x')
			{
				x = va_arg(valist, unsigned int);
				if (x < 0)
					x = UINT32_MAX - x;
				string = ft_itoahex(x);
			}
			if (prec > 0 && prec < (int)ft_strlen(string) && bols == 1)
			{
				string = ft_substr(string, 0, prec);
			}
			else if (bolprec == 1 && prec == 0 && (bols == 1 || d == 0 || x == 0))
				string = ft_strdup("");
			else if (prec > 0 && prec > (int)ft_strlen(string))
			{
				if (bols == 0)
				{
					auxd = prec - (int)ft_strlen(string);
				}
			}
			if (width > 0)
				aux = width - (int)ft_strlen(string) - auxd;
			while (aux-- > 0)
			{
				ft_putchar(' ');
				n++;
			}
			while (auxd-- > 0)
			{
				ft_putchar('0');
				n++;
			}
			ft_putstr(string);
			n += (int)ft_strlen(string);
			str++;
		}
		else
		{
			ft_putchar(*str);
			n++;
			str++;
		}
		bols = 0;
		bolprec = 0;
		width = 0;
		prec = 0;
		bolw = 0;
		aux = 0;
		auxd = 0;
	}
	return (n);
}

/*int	main()
{
ft_printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
}*/