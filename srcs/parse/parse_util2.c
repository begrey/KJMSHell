/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:29:02 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 09:33:57 by sunmin           ###   ########.fr       */
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

void	token_num_plus(char **s, int *ret)
{
	if (is_token((*s)) == 1)
		(*ret)++;
	else if (is_token((*s)) == 2)
	{
		(*ret)++;
		(*s)++;
	}
}

int		is_token_quote(const char *str)
{
	char		*s;
	char		flag;
	int			ret;

	ret = 1;
	flag = 0;
	s = (char *)str;
	if (is_token(s) && !is_token(s + 1))
		return (1);
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			token_num_plus(&s, &ret);
			if (is_token(s) && !is_token(s + 1) && *(s + 1))
			{
				ret++;
			}
		}
		s++;
	}
	if (is_token(s - 2))
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
