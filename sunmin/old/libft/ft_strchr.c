/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:29:25 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/12 20:28:48 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *str, int c)
{
	char	*p;

	p = (char *)str;
	while (*p != '\0')
	{
		if (*p == c)
			return (p);
		p++;
	}
	if (c == '\0')
		return (p);
	return (NULL);
}
