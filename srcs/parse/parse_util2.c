/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:29:02 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 19:17:41 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strerror(char *s)
{
	char *temp;

	temp = s;
	printf("%s", temp);
	return (-1);
}

int		is_token(char *s)
{
	if (*s == ';' || *s == '|' || (*s == '>' && *(s + 1) != '>') || *s == '<')
		return (1);
	else if (*s == '>' && *(s + 1) == '>')
		return (2);
	return (0);
}

int		is_token_quote(const char *str)		// 여기가 문제임
{
	char		*s;
	char		flag;
	int			ret;

	ret = 0;
	flag = 0;
	s = (char *)str;
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (is_token(s) == 1)
				ret++;
			else if (is_token(s) == 2)
			{
				ret++;
				s++;
			}
			if (is_token(s) && !is_token(s + 1) && *(s + 1))
				ret++;
		}
		s++;
	}
	if(*s)
		ret++;
	return (ret);
}

int		where_token(char *str)
{
	char		*s;
	char		flag;
	int			ret;
	int			i;

	i = 0;
	s = (char *)str;
	ret = 0;
	flag = 0;
	while (s[i])
	{
		flag = flag_check(s[i], flag);
		if (!flag)
		{
			if (is_token(&(s[i])))
				return (i);
		}
		i++;
	}
	return (i);
}
