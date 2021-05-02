/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*   Created: 2021/05/01 13:50:58 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/02 17:09:40 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		init_env(char *envp[])
{
	int		i;
	int		len;
	t_env	*temp;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	len = i;
	temp = (t_env *)malloc(sizeof(t_env) * (len));
	env = ft_listnew(find_key(envp[0]), find_value(envp[0]));
	i = 0;
	while (i < len)
	{
		temp[i].key = find_key(envp[i]);
		temp[i].value = find_value(envp[i]);
		temp[i].if_value = 1;
		ft_listadd_back(&env, &temp[i]);
		i++;
	}
	return (0);
}

char	*find_key(char *s)
{
	int		i;
	int		equal;
	char	*key;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	equal = i - 1;
	s[equal] = '\0';
	key = ft_strdup(s);
	return (key);
}

char	*find_value(char *s)
{
	char	*value;
	int		i;
	int		equal;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	equal = i + 1;
	if (equal == (int)ft_strlen(s))
		return (NULL);
	value = ft_strdup(s + equal);
	return (value);
}
