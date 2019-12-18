/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:58:23 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/18 13:15:45 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int i = 0;
	unsigned int len;

	len = ft_strlen(s);
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	if (len == i && *s != c)
		return (NULL);
	return ((char *)s);
}

int main(int argc, char **argv)
{
	int used[255];
	int x = 0, y;

	if (argc == 3)
	{
		while (x++ < 255)
			used[x] = 0;
		x = 1;
		y = 0;
		while (argv[1][y])
		{
			if (!used[((unsigned char)argv[1][y])] && ft_strchr(argv[2], argv[1][y]))
			{
				used[((unsigned char)argv[1][y])] = 1;
				write(1, &argv[1][y],1);
			}
			y++;
		}
		x++;
		write(1, "\n",1);
	}
}