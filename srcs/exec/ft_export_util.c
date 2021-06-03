/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:00:42 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 14:04:47 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_if_value_export(t_env *temp, char *value)
{
	int		if_value;

	if_value = 1;
	temp->if_value = if_value;
	free(temp->value);
	temp->value = ft_strdup(value);
}

char	*extract_env(char *str, t_env *env)
{
	char	*s;
	char	*ret;
	t_env	*ex;

	if (*str != '$')
		return (ft_strdup(str));
	else if (str[0] == '$' && str[1] == '\0')
		return (ft_strdup(str));
	s = str + 1;
	ex = ft_envfind(&env, s);
	if (!ex)
	{
		ret = ft_strdup("");
		return (ret);
	}
	ret = ft_strdup(ex->value);
	if (!ret)
		ret = ft_strdup("");
	return (ret);
}

void	make_no_value_export(char *ex_env, t_env *env)
{
	int		if_value;
	char	*value;
	t_env	*temp;

	value = NULL;
	if_value = 0;
	temp = ft_envfind(&env, ex_env);
	if (temp == NULL)
	{
		ft_envadd_back(&env, ft_envnew(ft_strdup(ex_env),
					ft_strdup(""), if_value));
	}
}

void	make_if_value_export(t_env *env, char *ex_env, char *value)
{
	t_env	*temp;
	int		if_value;

	if_value = 1;
	temp = ft_envfind(&env, ex_env);
	if (temp == NULL)
	{
		ft_envadd_back(&env, ft_envnew(ft_strdup(ex_env),
					ft_strdup(value), if_value));
	}
}

void	if_value_or_not(t_line **tmp, int *if_value, char **value, t_env *env)
{
	char	*temp;

	if (ft_strchr(((*tmp)->arg), '=') != 0)
	{
		(*if_value) = 1;
		temp = find_value((*tmp)->arg);
		(*value) = convert_env(temp, env);
		free(temp);
	}
	else
	{
		(*if_value) = 0;
		(*value) = NULL;
	}
}
