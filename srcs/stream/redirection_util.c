/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:11:09 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 17:13:38 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

void		put_left_or_right(t_line **temp, int *type)
{
	if ((*temp)->arg[0] == '<')
	{
		(*type) = 3;
		(*temp) = (*temp)->next;
	}
	else
	{
		(*type) = 1;
		if ((*temp)->arg[1] == '>')
			(*type) = 2;
		(*temp) = (*temp)->next;
	}
}

void		next_temp_flag(t_line **temp, int *flag)
{
	(*temp) = (*temp)->next;
	(*flag)++;
}

void		put_redir(t_line *line, char ***re_name, int **re_type, int i)
{
	int		flag;
	int		type;
	t_line	*temp;

	temp = line;
	while (temp)
	{
		type = 0;
		if (is_redir(temp->arg[0]))
		{
			put_left_or_right(&temp, &type);
			flag = 0;
			while (temp && !is_redir(temp->arg[0]))
			{
				if (flag == 0)
				{
					(*re_type)[++i] = type;
					(*re_name)[i] = ft_strdup(temp->arg);
				}
				next_temp_flag(&temp, &flag);
			}
		}
		if (temp && !is_redir(temp->arg[0]))
			temp = temp->next;
	}
}

int			redir_num(t_line *line)
{
	int		num;
	t_line	*temp;

	num = 0;
	temp = line;
	while (temp)
	{
		if (is_redir(temp->arg[0]))
		{
			temp = temp->next;
			if (is_redir(temp->arg[0]))
				temp = temp->next;
			while (temp && !is_redir(temp->arg[0]))
				temp = temp->next;
			num++;
		}
		if (temp && !is_redir(temp->arg[0]))
			temp = temp->next;
	}
	return (num);
}
