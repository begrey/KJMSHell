/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:48:46 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 13:55:02 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pip_exit(int pip_flag)
{
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
	pip_exit(pip_flag);
}
