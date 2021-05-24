/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:29:12 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/16 15:41:37 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char	*temp;
	const char		*s;

	if (!dest && !src)
		return (NULL);
	temp = dest;
	s = src;
	if (dest <= src)
	{
		while (num--)
			*temp++ = *s++;
	}
	else
	{
		temp += num;
		s += num;
		while (num--)
			*--temp = *--s;
	}
	return (dest);
}
