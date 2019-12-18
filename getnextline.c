/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:56:35 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/18 15:43:18 by iromero-         ###   ########.fr       */
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

int	main()
{
	char *s = ft_strdup("hola");
	char *s2 = ft_strdup("bb");
	printf("%s", ft_strjoin(s, s2));
}