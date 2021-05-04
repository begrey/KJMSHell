/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/03 15:50:57 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*exec_export(char **command_line, int len)
{
	int		i;
	char	*str;
	t_env	*temp;
	t_env	*idx;

	str = ft_strdup("");
	if (command_line[1] == NULL)
	{
		idx = env;		// 임시 변수를 사용하지 않으면 한번밖에 사용할 수 없음
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
	else
	{
		temp = (t_env *)malloc(sizeof(t_env) * (len));
		i = 1;
		while (command_line[i])
		{
			if ((command_line[i][0] >= 'A' && command_line[i][0] <= 'Z') || (command_line[i][0] >= 'a' && command_line[i][0] <= 'z') || command_line[i][0] == '$')
			{
				if (ft_listfind(&env, extract_env(find_key(command_line[i]))))
					temp = ft_listfind(&env, extract_env(find_key(command_line[i])));
				else
				{
					(*temp).key = extract_env(find_key(command_line[i]));
					ft_listadd_back(&env, temp);
				}
				if (ft_strchr(command_line[i], '=') != 0)
				{
					(*temp).if_value = 1;
					(*temp).value = extract_env(find_value(command_line[i]));
				}
				else
					(*temp).if_value = 0;

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
	return (str);
}

char	*exec_env(char **command_line, int len)
{
	t_env	*idx;
	char	*str;

	if (len > 1)
	{
		str = ft_strdup("env: No such file or directory\n");
		return (str);
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
	return (str);
}

char	*exec_unset(char **command_line, int len)
{
	t_env	*now;
	t_env	*begin;
	int		i;

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
	return (NULL);
	command_line = NULL;
	len = 0;
}

char	*extract_env(char *str)
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
	ex = ft_listfind(&env, s);
	ret = ex->value;
	if (!ret)
		ret = ft_strdup("");
	return (ret);
}
