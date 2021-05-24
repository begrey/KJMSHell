/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/24 16:30:40 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exec_export(t_line *line, t_env *env)
{
	int		i;
	char	*str;
	t_env	*temp;
	t_env	*idx;
	int		len;
	char	**command_line;

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

	str = ft_strdup("");
	if (command_line[1] == NULL)			// export 단독으로 들어왔을 때
	{
		ft_env_sort(&env);// idx 정렬 한번 하기
		idx = env;
		while (idx)
		{
			str = ft_strjoin(str, "declare -x ");
			str = ft_strjoin(str, idx->key);		// 메모리 릭 체크해야
			if (idx->if_value)
			{
				str = ft_strjoin(str, "=");
				str = ft_strjoin(str, "\"");
				str = ft_strjoin(str, idx->value);
				str = ft_strjoin(str, "\"");
			}
			str = ft_strjoin(str, "\n");
			idx = idx->next; 
		}
	}
	else						// export 이외에 인자가 있을
	{
		temp = (t_env *)malloc(sizeof(t_env) * (len));
		i = 1;
		while (command_line[i])
		{
			if ((command_line[i][0] >= 'A' && command_line[i][0] <= 'Z') || (command_line[i][0] >= 'a' && command_line[i][0] <= 'z') || command_line[i][0] == '$')
			{
				if (ft_envfind(&env, extract_env(find_key(command_line[i]), env)))
					temp = ft_envfind(&env, extract_env(find_key(command_line[i]), env));
				else
				{
					(*temp).key = extract_env(find_key(command_line[i]), env);
					ft_envadd_back(&env, temp);
				}
				if (ft_strchr(command_line[i], '=') != 0)
				{
					(*temp).if_value = 1;
					(*temp).value = extract_env(find_value(command_line[i]), env);
				}
				else
				{
					(*temp).if_value = 0;
				}

			}
			else		// 변수명이 숫자나 특수문자로 시작하면 안됨
			{
				str = ft_strjoin(str, "export: ");
				str = ft_strjoin(str, &command_line[i][0]);
				str = ft_strjoin(str, ": not a valid identifier\n");
			}

			i++;
			temp++;
		}
	}
	write(1, str, ft_strlen(str));
}

void	exec_env(t_line *line, t_env *env)
{
	t_env	*idx;
	char	*str;
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
		str = ft_strdup("env: No such file or directory\n");
		return ;
	}
	str = ft_strdup("");
	if (command_line[1] == NULL)
	{
		idx = env;
		while (idx)
		{
			if (idx->if_value)
			{
				str = ft_strjoin(str, idx->key);
				str = ft_strjoin(str, "=");
				str = ft_strjoin(str, idx->value);
				str = ft_strjoin(str, "\n");
			}
			idx = idx->next; 
		}
	}
	write(1, str, ft_strlen(str));
}

void	exec_unset(t_line *line, t_env *env)
{
	t_env	*now;
	t_env	*begin;
	int		i;
	int		len;
	char	**command_line;

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
			if (ft_strcmp(begin->key, find_key(command_line[i])) == 0)
			{
				if (now->next)
					now->next = begin->next;
			}
			now = begin;
			begin = begin->next;
		}
		i++;
	}
}

char	*extract_env(char *str, t_env *env)
{
	char	*s;
	char	*ret;
	t_env	*ex;

	if (*str != '$')
		return (str);
	else if (str[0] == '$' && str[1] == '\0')
	{
		return (str);
	}
	s = str + 1;
	ex = ft_envfind(&env, s);
	ret = ex->value;
	if (!ret)
		ret = ft_strdup("");
	return (ret);
}
