/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/02 17:37:42 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exec_export(t_line *line, t_env *env, int pip_flag)
{
	int		i;
	t_env	*temp;
	t_env	*idx;
	int		len;
	char	**command_line;
	char	*ex_env;
	char	*key;
	char	*value;
	int		if_value;
	char	*ttemp;

	len = ft_listsize(line);
	command_line = (char **)malloc(sizeof(char *) * (len + 1));
	command_line[len] = NULL;
	i = 0;
	while (i < len)
	{
		command_line[i] = ft_strdup(line->arg);
		i++;
		line = line->next;
	}
	if (command_line[1] == NULL)
	{
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
	else
	{
		i = 1;
		while (command_line[i])
		{
			key = find_key(command_line[i]);
			ex_env = extract_env(key, env);
			free(key);
			if (is_alpha(command_line[i][0]) || is_dollar(command_line[i][0]))
			{
				if (ft_strchr(command_line[i], '=') != 0)
				{
					if_value = 1;
					ttemp = find_value(command_line[i]);
					value = convert_env(ttemp, env);
					free(ttemp);
				}
				else
				{
					if_value = 0;
					value = NULL;
				}
				if ((ft_envfind(&env, ex_env)) && if_value == 1)
				{
					temp = ft_envfind(&env, ex_env);
					temp->if_value = if_value;
					free(temp->value);
					temp->value = ft_strdup(value);
				}
				else
				{
					ttemp = find_key(command_line[i]);
					key = extract_env(ttemp, env);
					free(ttemp);
					if (value == NULL)
					{
						ft_envadd_back(&env, ft_envnew(ft_strdup(key), ft_strdup(""), if_value));
					}
					else
						ft_envadd_back(&env, ft_envnew(ft_strdup(key), ft_strdup(value), if_value));
					free(key);
				}
				free(value);
			}
			else
				printf("export: %s: not a valid identifier\n", command_line[i]);
			free(ex_env);
			i++;
			temp++;
		}
	}
	free_split(command_line);
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
	if (pip_flag == 0)
		exit(0);
}

void	exec_unset(t_line *line, t_env *env, int pip_flag)
{
	t_env	*now;
	t_env	*begin;
	int		i;
	int		len;
	char	**command_line;
	char	*key;

	len = ft_listsize(line);
	command_line = (char **)malloc(sizeof(char *) * (len + 1));
	command_line[len] = NULL;
	i = -1;
	while (++i < len)
	{
		command_line[i] = ft_strdup(line->arg);
		line = line->next;
	}
	i = 0;
	while (++i < len)
	{
		now = begin;
		begin = env;
		while (begin)
		{
			key = find_key(command_line[i]);
			if (ft_strcmp(begin->key, key) == 0)
			{
				if (now->next)
					now->next = begin->next;
			}
			now = begin;
			begin = begin->next;
			free(key);
		}
	}
	free_split(command_line);
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
