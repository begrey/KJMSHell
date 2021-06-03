/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:36:21 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:03:38 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe		*ft_pipenew(void)
{
	t_pipe	*lst;

	if (!(lst = (t_pipe *)malloc(sizeof(t_pipe) * 1)))
		return (NULL);
	lst->next = NULL;
	return (lst);
}

t_pipe		*ft_pipelast(t_pipe *lst)
{
	t_pipe	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void		ft_pipeadd_back(t_pipe **pip, t_pipe *new)
{
	t_pipe	*last;
	t_pipe	*temp;

	temp = *pip;
	if (temp == NULL)
	{
		*pip = new;
		new->next = NULL;
		return ;
	}
	temp = *pip;
	last = ft_pipelast(temp);
	last->next = new;
}

int			ft_pipesize(t_line *list)
{
	t_line	*temp;
	int		pip;

	pip = 0;
	temp = list;
	while (temp != NULL)
	{
		if (temp->arg[0] == '|')
			pip++;
		temp = temp->next;
	}
	return (pip);
}
