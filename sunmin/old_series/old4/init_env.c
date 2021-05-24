/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:09:40 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/21 11:34:12 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
}

