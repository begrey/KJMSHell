/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:57:12 by begrey            #+#    #+#             */
/*   Updated: 2020/10/12 15:03:06 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *str, int c)
{
	char		*ptr;
	int			len;

	len = ft_strlen(str) - 1;
	ptr = (char *)str;
	while (*ptr != '\0')
		ptr++;
	if (c == '\0')
		return (ptr);
	while (len >= 0)
	{
		ptr--;
		if (*ptr == c)
			return (ptr);
		len--;
	}
	return (NULL);
}
