/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:24:02 by sunmin            #+#    #+#             */
/*   Updated: 2021/04/27 11:54:19 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./MsHell.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *str1;
	unsigned char *str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n--)
	{
		if (*str1 != *str2 || *str1 == '\0' || *str2 == '\0')
			return ((int)(*str1 - *str2));
		else
		{
			str1++;
			str2++;
		}
	}
	return (0);
}

size_t				ft_strlen(const char *str)
{
	int				i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char				*ft_strdup(const char *s)
{
	char			*str;
	int				len;
	int				i;

	len = ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	size_t			len1;
	size_t			len2;
	size_t			i;
	size_t			j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < len1 + len2)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char				*is_new(char *s, char c)
{
	int				i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
}
