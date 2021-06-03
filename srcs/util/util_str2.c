/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_str2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:43:14 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 15:44:27 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strcmp(char *dest, char *src)
{
	int i;

	i = 0;
	while (dest[i] != '\0' || src[i] != '\0')
	{
		if (dest[i] > src[i])
			return (dest[i] - src[i]);
		else if (dest[i] < src[i])
			return (dest[i] - src[i]);
		i++;
	}
	return (0);
}

char	*ft_joinfree1(char **s1, char **s2)
{
	char	*str;

	str = ft_strjoin(*s1, *s2);
	free(*s1);
	return (str);
}

char	*str_append1(char *s1, char *s2)
{
	char	*str;

	str = ft_joinfree1(&s1, &s2);
	return (str);
}

char	*ft_joinfreechar(char **s1, char *s2)
{
	char	*str;

	str = ft_strjoin(*s1, s2);
	free(*s1);
	return (str);
}

char	*str_appendchar(char *s1, char c)
{
	char	*str;

	str = ft_joinfreechar(&s1, &c);
	return (str);
}
