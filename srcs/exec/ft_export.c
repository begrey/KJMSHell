/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/08 10:49:27 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_no_value_export(t_env *temp)
{
	int		if_value;

	if_value = 0;
	free(temp->value);
	temp->value = NULL;
	temp->if_value = if_value;
}

void	when_env_no_exist(int if_value, t_env *env, char *ex_env, char *value)
{
	if (if_value)
		make_if_value_export(env, ex_env, value);
	else
		make_no_value_export(ex_env, env);
}

void	when_env_exist(int if_value, t_env *temp, char *value)
{
	if (if_value)
		put_if_value_export(temp, value);
	else
		put_no_value_export(temp);
}

void	put_export(t_line *tmp, char *key, char *value, t_env *env)
{
	char	*ex_env;
	t_env	*temp;
	int		if_value;

	while (tmp)
	{
		key = find_key(tmp->arg);
		ex_env = extract_env(key, env);
		temp = ft_envfind(&env, ex_env);
		if (is_alpha_dollar_str(key))
		{
			if_value_or_not(&tmp, &if_value, &value, env);
			if ((ft_envfind(&env, ex_env)))
				when_env_exist(if_value, temp, value);
			else
				when_env_no_exist(if_value, env, ex_env, value);
			free(value);
		}
		else
			printf("export: %s: not a valid identifier\n", tmp->arg);
		free(key);
		free(ex_env);
		tmp = tmp->next;
	}
}

void	exec_export(t_line *line, t_env *env, int pip_flag)
{
	t_line	*tmp;
	char	*key;
	char	*value;
	int		len;

	tmp = line->next;
	len = ft_listsize(line);
	if (tmp == NULL)
		printf_export(env);
	else
	{
		key = NULL;
		value = NULL;
		put_export(tmp, key, value, env);
	}
	if (pip_flag == 0)
		exit(0);
}
