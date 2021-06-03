/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:24:15 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 18:41:09 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*put_return_value(char *res)
{
	res = (char *)malloc(sizeof(char) * 3);
	res[0] = '$';
	res[1] = '?';
	res[2] = '\0';
	return (res);
}

int			check_env_len(const char *str)
{
	char	*s;
	int		len;

	len = 0;
	s = (char *)str;
	if (*s == '$')
		s++;
	if (*s == '?' || iis_num(*s))
		return (1);
	while (*s && (is_alpha(*s) || iis_num(*s)))
	{
		len++;
		s++;
	}
	return (len);
}

int			check_flag(char c, int flag)
{
	if (flag == 0)
	{
		if (c == '\'')
			flag = 1;
	}
	else
	{
		if (c == '\'')
			flag = 0;
	}
	return (flag);
}
