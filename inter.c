/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:58:23 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/18 20:11:25 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t i = 0;

	while (s[i]!= '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int len = ft_strlen(s);
	unsigned int i = 0;
	while (*s != c && *s)
	{
		s++;
		i++;
	}
	if (len == i && *s != c)
		return (NULL);
	return ((char *)s);
}

int	main(int argc, char **argv)
{
	int used[255];
	int x = 0;

	if (argc == 3)
	{
		while(x < 255)
			used[x++] = 0;
		x = 0;
		while (argv[1][x])
		{
			if (!used[(unsigned char)argv[1][x]] && ft_strchr(argv[2], argv[1][x]))
			{
				used[(unsigned char)argv[1][x]] = 1;
				write(1, &argv[1][x], 1);
			}
			x++;
		}
		write (1, "\n", 1);
	}
	return (0);
}