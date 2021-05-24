/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:38:58 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/05 16:15:10 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	val;
	char			*ptr;
	unsigned long	i;

	i = 0;
	ptr = dest;
	val = (unsigned char)c;
	while (i < len)
		ptr[i++] = val;
	return (dest);
}
