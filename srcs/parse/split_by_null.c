/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:48:22 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 15:59:47 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_listiter(t_line *lst)
{
	int		i;
	t_line	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

t_line		*ft_list_null_term(t_line *lst, int index)
{
	int		i;
	t_line	*temp;
	t_line	*free_temp;

	i = 0;
	while (lst != NULL)
	{
		if (i == (index - 1))
		{
			if (lst->next == NULL)
				temp = lst->next;
			else
				temp = lst->next->next;
			free_temp = lst->next;
			free(free_temp);
			lst->next = NULL;
			return (temp);
		}
		lst = lst->next;
		i++;
	}
	return (lst);
}

int			ft_split_list_token(t_line *lst, char token)
{
	int		i;
	t_line	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		if (temp->arg[0] == token)
		{
			free(temp->arg);
			return (i);
		}
		i++;
		temp = temp->next;
	}
	return (i);
}

void		ft_move_temp(t_line **temp, int i)
{
	while (temp != NULL && i != 0)
	{
		*temp = (*temp)->next;
		i--;
	}
}

void		split_by_semi(t_line *line, t_env *env)
{
	t_line	*temp;
	t_line	*iter;
	int		i;
	int		j;

	j = 0;
	temp = line;
	iter = line;
	while (temp != NULL)
	{
		i = ft_split_list_token(temp, ';');
		temp = ft_list_null_term(temp, i);
		ft_listiter(iter);
		split_by_pipe(iter, env);
		iter = temp;
	}
}
