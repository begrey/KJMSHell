/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:34:27 by sunmin            #+#    #+#             */
/*   Updated: 2020/10/10 21:48:18 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		start;
	size_t		end;

	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]))
	{
		if (end - 1 < 1)
			break ;
		--end;
	}
	if (start > end)
		return (ft_strdup(""));
	if (!(str = (char *)malloc(sizeof(char) * (end - start + 1))))
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
