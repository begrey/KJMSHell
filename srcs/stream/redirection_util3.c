/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:11:37 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 17:15:21 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		delete_escape_list(t_line *line)
{
	t_line	*temp;
	char	*str;

	temp = line;
	while (temp)
	{
		str = temp->arg;
		temp->arg = delete_escape(temp->arg);
		free(str);
		temp = temp->next;
	}
}

void		del_qoute_list(t_line *line)
{
	t_line	*temp;
	char	*str;

	temp = line;
	while (temp)
	{
		str = temp->arg;
		(temp)->arg = ft_del_quote((temp)->arg);
		free(str);
		temp = (temp)->next;
	}
}

void		restore_escape_list(t_line *line)
{
	t_line	*temp;
	char	*str;

	temp = line;
	while (temp)
	{
		str = temp->arg;
		temp->arg = restore_escape(temp->arg);
		free(str);
		temp = temp->next;
	}
}

int			redirection_open(int **fd, int re_num, int *re_type, char **re_name)
{
	int		i;
	int		j;

	j = -1;
	i = -1;
	(*fd) = (int *)malloc(sizeof(int) * 2);
	(*fd)[1] = -1;
	while (++i < re_num)
	{
		if (re_type[i] == 1)
			(*fd)[1] = open(re_name[i], O_RDWR | O_CREAT | O_TRUNC, 00777);
		else if (re_type[i] == 2)
			(*fd)[1] = open(re_name[i], O_RDWR | O_APPEND | O_CREAT, 00777);
		else if (re_type[i] == 3)
		{
			j = i;
			if (((*fd)[0] = open(re_name[i], O_RDONLY, 00777)) < 0)
			{
				printf("%s\n", strerror(errno));
				return (-2);
			}
		}
	}
	return (j);
}
