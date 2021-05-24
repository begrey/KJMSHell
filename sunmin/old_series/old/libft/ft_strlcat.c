/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:29:37 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/16 15:23:20 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_len(char *dest)
{
	size_t	len;

	len = 0;
	while (*dest != '\0')
	{
		len++;
		dest++;
	}
	return (len);
}

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	int		i;
	int		len;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = count_len((char *)src);
	i = 0;
	while (i++ < (int)dest_len)
		dest++;
	i = 0;
	len = (int)(size - dest_len - 1);
	while (len > 0 && i < len && *src != '\0')
	{
		*dest = *(char *)src;
		dest++;
		src++;
		i++;
	}
	if (size > dest_len)
		*dest = '\0';
	if (size > dest_len)
		return (src_len + dest_len);
	else
		return (src_len + size);
}
