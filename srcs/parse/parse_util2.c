/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:29:02 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/08 10:03:16 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_token(char *s)
{
	if (*s == ';' || *s == '|' || (*s == '>' && *(s + 1) != '>') || *s == '<')
	{
		return (1);
	}
	else if (*s == '>' && *(s + 1) == '>')
		return (2);
	return (0);
}

void	token_num_plus(char **s, int *ret)
{
	if (is_token((*s)) == 1)
	{
		(*ret)++;
	}
	else if (is_token((*s)) == 2)
	{
		(*ret)++;
		(*s)++;
	}
}

void	if_not_flag(char *flag, char **s, int *ret)
{
	if (!(*flag))
	{
		if (is_token((*s)))
		{
			token_num_plus(&(*s), &(*ret));
			(*s)++;
			if (*(*s) && !is_token((*s)))
			{
				(*ret)++;
				(*s)++;
			}
		}
		else
		{
			if (!is_token((*s)) && is_token((*s) - 1))
				(*ret)++;
			(*s)++;
		}
	}
	else
		(*s)++;
}

int		is_token_quote(const char *str, char flag)
{
	char		*s;
	int			ret;

	ret = 0;
	s = (char *)str;
	if (*s)
	{
		flag = flag_check(*s, flag);
		ret += 1;
		s++;
	}
	flag = flag_check(*s, flag);
	if (*s && ((!is_token(s) && is_token(s - 1))
	|| (is_token(s) && !is_token(s - 1))))
		ret += 1;
	if (*s)
		s++;
	flag = flag_check(*s, flag);
	while (*s)
	{
		flag = flag_check(*s, flag);
		if_not_flag(&flag, &s, &ret);
	}
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
