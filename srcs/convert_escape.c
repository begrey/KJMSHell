/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_escape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:48:23 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/02 16:09:00 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void		convert_minus_escape(int flag, char **s, int *i, char **result)
{
	if (flag == '\"')
	{
		if ((*(*s)) == '\\' && *((*s) + 1) == '$')
		{
			s++;
			(*i)++;
			(*result)[*i] = -1 * (*(*s));
		}
	}
}

void		init_var(int *i, int *flag)
{
	*i = -1;
	*flag = 1;
}

char		*convert_escape(char *s)
{
	char	*result;
	int		flag;
	int		i;

	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	result[ft_strlen(s)] = '\0';
	init_var(&i, &flag);
	while (*s)
	{
		result[++i] = *s;
		flag = flag_check(*s, flag);
		if (flag)
			convert_minus_escape(flag, &s, &i, &result);
		else
		{
			if ((*s) == '\\')
			{
				s++;
				i++;
				result[i] = -1 * (*s);
			}
		}
		s++;
	}
	return (result);
}

int			check_escape(char *s)
{
	int		flag;
	int		num;

	flag = 0;
	num = 0;
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (*s == '\\')
				num++;
		}
		s++;
	}
	return (num);
}

char		*delete_escape(char *s)
{
	char	*result;
	int		num;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	num = check_escape(s);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) - num + 1));
	result[ft_strlen(s) - num] = '\0';
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (*s == '\\')
				s++;
		}
		result[i] = *s;
		i++;
		s++;
	}
	return (result);
}

char		*restore_escape(char *s)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	result[ft_strlen(s)] = '\0';
	i = 0;
	while (*s)
	{
		if (*s < 0)
			*s *= -1;
		result[i] = *s;
		s++;
		i++;
	}
	return (result);
}
