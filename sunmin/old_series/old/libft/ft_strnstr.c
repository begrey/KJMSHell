/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:13:15 by begrey            #+#    #+#             */
/*   Updated: 2020/10/16 18:47:05 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char *b, char *l, size_t len, size_t len_temp)
{
	size_t	i;

	i = len_temp;
	while (*b != '\0' && *l != '\0')
	{
		if (i == len || *b != *l)
			return (-1);
		b++;
		l++;
		i++;
	}
	if (*l == '\0')
		return (1);
	return (-1);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*b;
	char	*l;
	char	*temp;

	i = 0;
	b = (char *)big;
	l = (char *)little;
	if (*l == '\0')
		return (b);
	while (*b != '\0' && i < len)
	{
		l = (char *)little;
		if (*b == *l)
		{
			temp = b;
			if (is_in(b, l, len, i) == 1)
				return (temp);
			b = temp;
		}
		b++;
		i++;
	}
	return (NULL);
}
