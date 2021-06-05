/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_envlist2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:35:14 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/05 14:13:42 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		put_return(int ret, t_env *env)
{
	t_env	*temp;
	char	*num;

	temp = env;
	num = ft_itoa(ret);
	while (temp)
	{
		if (temp->key[0] == '?')
		{
			free(temp->value);
			temp->value = num;
		}
		temp = temp->next;
	}
}

int			return_return(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->key[0] == '?')
		{
			return (atoi(temp->value));
		}
		temp = temp->next;
	}
	return (0);
}

char		*find_key(const char *str)
{
	int		i;
	int		equal;
	char	*key;
	int		flag;

	flag = 0;
	key = ft_strdup((char *)str);
	equal = 0;
	i = 0;
	while (key[i])
	{
		if (key[i] == '=' && flag == 0)
		{
			equal = i;
			flag = 1;
		}
		i++;
	}
	if (equal == 0)
		equal = i;
	key[equal] = '\0';
	return (key);
}

char		*find_value(const char *str)
{
	char	*value;
	char	*result;
	int		i;
	int		equal;
	int		flag;

	flag = 0;
	value = (char *)str;
	equal = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '=' && flag == 0)
		{
			equal = i;
			flag = 1;
		}
		i++;
	}
	result = ft_strdup(value + equal + 1);
	return (result);
}
