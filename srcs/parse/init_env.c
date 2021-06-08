/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:28:21 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/08 11:10:11 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**make_envp(t_env *env, int key)
{
	t_env	*temp;
	char	*v_temp;
	char	*value;
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * (key + 1));
	key = 0;
	temp = env;
	while (temp)
	{
		if (temp->if_value && temp->key[0] != '?')
		{
			v_temp = ft_strjoin(temp->key, "=");
			value = ft_strjoin(v_temp, temp->value);
			free(v_temp);
			envp[key++] = value;
		}
		temp = temp->next;
	}
	envp[key] = NULL;
	return (envp);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		key;
	t_env	*temp;

	key = 0;
	temp = env;
	while (temp)
	{
		key++;
		temp = temp->next;
	}
	key--;
	envp = make_envp(env, key);
	return (envp);
}
