/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 08:48:40 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	printf_export(t_env *env)
{
	t_env	*idx;

	ft_env_sort(&env);
	idx = env;
	while (idx)
	{
		if (idx->key[0] != '?')
		{
			printf("declare -x %s", idx->key);
			if (idx->if_value)
				printf("=\"%s\"", idx->value);
			printf("\n");
		}
		idx = idx->next;
	}
}

int		is_alpha_dollar_str(char *s)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (!(*str >= 'A' && *str <= 'Z') &&
				!(*str >= 'a' && *str <= 'z') && *str != '$')
			return (0);
		str++;
	}
	return (1);
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

void	put_if_value_export(t_env *temp, char *value)
{
	int		if_value;

	if_value = 1;
	temp->if_value = if_value;
	free(temp->value);
	temp->value = ft_strdup(value);
}

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
		free(key);
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

void	print_env(t_env *idx)
{
	while (idx)
	{
		if (idx->key[0] != '?' && idx->if_value)
			printf("%s=%s\n", idx->key, idx->value);
		idx = idx->next;
	}
}

void	pip_exit(int pip_flag)
{
	if (pip_flag == 0)
		exit(0);
}

void	exec_env(t_line *line, t_env *env, int pip_flag)
{
	t_env	*idx;
	char	**command_line;
	int		len;
	int		i;

	idx = env;
	len = ft_listsize(line);
	command_line = (char **)malloc(sizeof(char *) * (len + 1));
	command_line[len] = NULL;
	i = -1;
	while (++i < len)
	{
		command_line[i] = ft_strdup(line->arg);
		line = line->next;
	}
	if (len > 1)
	{
		printf("env: No such file or directory\n");
		free_split(command_line);
		return ;
	}
	if (command_line[1] == NULL)
		print_env(idx);
	free_split(command_line);
	pip_exit(pip_flag);
}

void	free_single_env(t_env *env)
{
	t_env *temp;

	temp = env;
	free(temp->key);
	free(temp->value);
	free(temp);
}

void	exec_unset(t_line *line, t_env *env, int pip_flag)
{
	t_env	*now;
	t_env	*begin;
	t_line	*temp;

	temp = line->next;
	while (temp)
	{
		begin = env;
		while (begin)
		{
			if ((now = ft_envfind(&env, temp->arg)))
			{
				if (now->prev)
					now->prev->next = now->next;
				if (now->next)
					now->next->prev = now->prev;
				free_single_env(now);
			}
			begin = begin->next;
		}
		temp = temp->next;
	}
	if (pip_flag == 0)
		exit(0);
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
