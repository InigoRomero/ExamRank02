/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:56:35 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/18 20:11:08 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t ft_strlen(const char *s)
{
	size_t i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int i = 0;
	unsigned int leng = 0;

	while (*s && *s != c)
	{
		i++;
		s++;
	}
	if (*s != c && i == leng)
		return (NULL);
	return ((char *)s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char*)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
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

static	int	getcharpls(char **line, char **aux, int n)
{
	char *temp;
	char *temp2;

	if (n < 0)
		return (-1);
	if (!n && !*aux)
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((temp = ft_strchr(*aux, '\n')))
	{
		*temp = 0;
		*line = ft_strdup(*aux);
		temp2 = ft_strdup(++temp);
		free(*aux);
		*aux = temp2;
	}
	else
	{
		*line = *aux;
		*aux = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char	buffer[BUFFER_SIZE +1];
	static char *aux[4096];
	int	n;
	char	*temp;

	if(fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	while ((n = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[n] = 0;
		if (!aux[fd])
			aux[fd] = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(aux[fd], buffer);
			free(aux[fd]);
			aux[fd] = temp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (getcharpls(line, &aux[fd], n));
}