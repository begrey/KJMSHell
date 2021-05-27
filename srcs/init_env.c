/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:28:21 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/27 14:52:50 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char *envp[])
{
	int		i;
	int		len;
	t_env	*temp;
	t_env	*env;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	len = i;
	temp = (t_env *)malloc(sizeof(t_env) * (len + 1));		// 비밀의 방까지
	env = ft_envnew(find_key(envp[0]), find_value(envp[0]));
	i = 0;
	while (i < len)
	{
		temp[i].key = find_key(envp[i]);
		temp[i].value = find_value(envp[i]);
		temp[i].if_value = 1;
		ft_envadd_back(&env, &temp[i]);
		i++;
	}
	temp[i].key = ft_strdup("?");
	temp[i].value = ft_strdup("0");
	temp[i].if_value = 0;
	ft_envadd_back(&env, &temp[i]);
	return (env);
}

