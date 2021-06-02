/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/02 11:13:36 by jimkwon          ###   ########.fr       */
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
	char	*ex_env;
	//env에 넣어둘 인자들
	char	*key;
	char	*value;
	int		if_value;
	char	*ttemp; // find_env free할놈


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
					printf("=\"%s\"", idx->value);
				printf("\n");
			}
			idx = idx->next; 
		}
		//write(1, str, ft_strlen(str)); 		// 수정해야 
	}
	else						// export 이외에 인자가 있을
	{
		//temp = (t_env *)malloc(sizeof(t_env) * (len));
		i = 1;
		while (command_line[i])
		{
			key = find_key(command_line[i]);
			ex_env = extract_env(key, env);
			free(key);
			if (is_alpha(command_line[i][0]) || is_dollar(command_line[i][0]))
			{
				if (ft_strchr(command_line[i], '=') != 0) //등호가 있을때
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
				if ((ft_envfind(&env, ex_env)) && if_value == 1)	// 기존 내용을 대체
				{
					temp = ft_envfind(&env, ex_env);
					temp->if_value = if_value;
					free(temp->value);
					temp->value = ft_strdup(value);
					//  printf("%p %p \n", temp->value, value);
					// printf("%s %s\n", temp->value, value);
				}
				else // 없을 때 새로 만드는 구간
				{
					ttemp = find_key(command_line[i]);
					key = extract_env(ttemp, env);
					free(ttemp);
					if (value == NULL)
					{
						ft_envadd_back(&env, ft_envnew(ft_strdup(key), ft_strdup(""), if_value));
						t_env *why = ft_envlast(env);
					}
					else
						ft_envadd_back(&env, ft_envnew(ft_strdup(key), ft_strdup(value), if_value));
					free(key);
				}
				//free(key);
				free(value);			
				// ttemp = ft_envlast(env)->value;
			//	 printf("%p %p \n", ttemp, value);
				// printf("%s %s \n", ttemp, value);
				// printf("%s\n", ttemp);
			}
			else		// 변수명이 숫자나 특수문자로 시작하면 안됨
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
		free_split(command_line);
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
	ret = ft_strdup(ex->value);
	if (!ret)
		ret = ft_strdup("");
	return (ret);
}
