/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:04:39 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/19 15:56:30 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, const char *set)
{
	char	*ptr;
	size_t	len;

	if (!s1)
		return (NULL);
	ptr = (char *)s1;
	while (ft_strchr(set, *(char *)s1) != NULL && *(char *)s1 != '\0')
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s1);
	while (*ptr != '\0')
		ptr++;
	ptr--;
	while (ft_strchr(set, *ptr) != NULL)
	{
		len--;
		ptr--;
	}
	return (ft_substr((char *)s1, 0, len));
}
