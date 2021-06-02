/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:28:21 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/02 14:58:27 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char *envp[], t_env *env)
{
	int		i;
	int		len;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	len = i;
	i = 0;
	while (i < len)
	{
		ft_envadd_back(&env, ft_envnew(find_key(envp[i]),
					find_value(envp[i]), 1));
		i++;
	}
	ft_envadd_back(&env, ft_envnew("?", ft_strdup("0"), 1));
	return (env);
}
