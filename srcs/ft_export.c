/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/01 11:39:25 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exec_export(t_line *line, t_env *env, int pip_flag)
{
	int		i;
	char	*str;
	t_env	*temp;
	t_env	*idx;
	int		len;
	char	**command_line;
	char	*str_temp;
	char	*key;
	char	*ex_env;


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


	//str = ft_strdup("");
	if (command_line[1] == NULL)			// export 단독으로 들어왔을 때
	{
		ft_env_sort(&env);// idx 정렬 한번 하기
		idx = env;
		while (idx)
		{
			if (idx->key[0] != '?')
			{
				printf("declare -x %s", idx->key);
				if (idx->if_value)
					printf("=\"%s\"\n", idx->value);
			}
			idx = idx->next; 
		}
		//write(1, str, ft_strlen(str)); 		// 수정해야 
	}
	else						// export 이외에 인자가 있을
	{
		temp = (t_env *)malloc(sizeof(t_env) * (len));
		i = 1;
		while (command_line[i])
		{
			if (is_alpha(command_line[i][0]) || is_dollar(command_line[i][0]))
			{
				key = find_key(command_line[i]);
				ex_env = extract_env(key, env);
				free(key);
				if ((temp = ft_envfind(&env, ex_env)))	
					temp = ft_envfind(&env, ex_env);
				else
				{
					(*temp).key = extract_env(find_key(command_line[i]), env);
				printf("aaa\n");
					ft_envadd_back(&env, temp);
				}
				if (ft_strchr(command_line[i], '=') != 0)
				{
					(*temp).if_value = 1;
//					(*temp).value = extract_env(find_value(command_line[i]), env);
					(*temp).value = convert_env(find_value(command_line[i]), env);
				}
				else
				{
					(*temp).if_value = 0;
				}
				free(ex_env);
			}
			else		// 변수명이 숫자나 특수문자로 시작하면 안됨
				printf("export: %s: not a valid identifier\n", command_line[i]);
			i++;
			temp++;
		}
	}
	
	free_split(command_line);
	if (pip_flag == 0)
		exit(0);
}

void	exec_env(t_line *line, t_env *env, int pip_flag)
{
	t_env	*idx;
	char	**command_line;
	int		len;
	int		i;

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

	if (len > 1)
	{
		printf("env: No such file or directory\n");
		return ;
	}
	if (command_line[1] == NULL)
	{
		idx = env;
		while (idx)
		{
			if (idx->key[0] != '?' && idx->if_value)
				printf("%s=%s\n", idx->key, idx->value);
			idx = idx->next; 
		}
	}

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
	char	*temp;
	char	*key;

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


	i = 1;
	while (i < len)
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
		i++;
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
	ret = ex->value;
	if (!ret)
		ret = ft_strdup("");
	return (ft_strdup(ret));
}
