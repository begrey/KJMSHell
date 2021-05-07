/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:55:53 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/16 16:18:19 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_word(char *s, int len)
{
	char	*p;
	char	*word;
	char	*word_p;

	if ((word = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	word_p = word;
	p = s;
	while (len != 0)
	{
		*word++ = *p++;
		len--;
	}
	*word = '\0';
	return (word_p);
}

static int	word_len(char *s, char c)
{
	int		len;

	len = 0;
	while (*s != '\0' && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	count_len(char *s, char c)
{
	int		len;

	len = 0;
	if (!s)
		return (0);
	while (*s == c && *s != '\0')
		s++;
	while (*s != '\0')
	{
		if (*s != c)
		{
			len++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (len);
}

static char	**free_ans(char **a)
{
	int	i;

	i = 0;
	while (a[i] != NULL)
		free(a[i++]);
	free(a);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**word;
	char	**ans;
	char	*ptr;

	ptr = (char *)s;
	if ((word = (char**)malloc(sizeof(char *) *
(count_len((char *)s, c) + 1))) == NULL)
		return (NULL);
	ans = word;
	while (ptr != NULL && *ptr != '\0')
	{
		if (*ptr != c)
		{
			if ((*word = get_word(ptr, word_len(ptr, c))) == NULL)
				return (free_ans(ans));
			word++;
			ptr = ft_strchr(ptr, c);
		}
		else
			ptr++;
	}
	*word = NULL;
	return (ans);
}
