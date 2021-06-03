/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:09:37 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 12:01:07 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_struct(t_line *list)
{
	t_line	*temp;

	temp = list;
	while (temp)
	{
		list = list->next;
		free(temp->arg);
		free(temp);
		temp = list;
	}
}

void		free_pipe(t_pipe *list)
{
	t_pipe *temp;

	temp = list;
	while (temp)
	{
		list = list->next;
		free(temp);
		temp = list;
	}
}

void		free_list_struct(t_line **list)
{
	int		i;
	t_line	*temp;

	i = 0;
	while (list[i] != NULL)
	{
		temp = list[i];
		while (temp)
		{
			list[i] = (list[i])->next;
			free(temp->arg);
			free(temp);
			temp = list[i];
		}
		i++;
	}
	free(list);
}
