/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:28:31 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/16 15:59:27 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			flag;

	flag = 0;
	ptr = (unsigned char *)src;
	while (*ptr != '\0' && flag < n)
	{
		if (*ptr == (unsigned char)c)
			break ;
		flag++;
		ptr++;
	}
	if (*ptr == '\0' || flag == n)
	{
		ft_memcpy(dest, src, n);
		if (flag == n)
			return (NULL);
		else
			return ((void *)(dest + n));
	}
	else
	{
		ft_memcpy(dest, src, flag + 1);
		return ((void *)(dest + (flag + 1)));
	}
}
