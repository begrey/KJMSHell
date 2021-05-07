/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:59:53 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/18 11:03:06 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	unsigned int	i;
	char			*str;

	if (!s)
		return (0);
	s_len = (int)ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i != start)
	{
		s++;
		i++;
	}
	i = 0;
	while (i < len && *s != '\0')
	{
		str[i++] = *(char *)s;
		s++;
	}
	str[i] = '\0';
	return (str);
}
