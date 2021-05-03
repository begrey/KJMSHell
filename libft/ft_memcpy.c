/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:29:01 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/16 16:14:42 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dest, const void *src, size_t num)
{
	unsigned char	*ptr;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < num)
	{
		*ptr = *s;
		ptr++;
		s++;
		i++;
	}
	return (dest);
}
