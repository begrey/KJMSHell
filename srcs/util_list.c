/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:55:36 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:57:21 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_listsize(t_line *line)
{
	t_line	*temp;
	int		len;

	len = 0;
	temp = line;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

t_line		*ft_listlast(t_line *lst)
{
	t_line	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_line		*ft_listnew(char *content)
{
	t_line	*lst;

	if (!(lst = (t_line *)malloc(sizeof(t_line) * 1)))
		return (NULL);
	lst->arg = content;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void		ft_listadd_back(t_line **lst, t_line *new)
{
	t_line	*last;
	t_line	*temp;

	temp = *lst;
	if (temp == NULL)
	{
		*lst = new;
		new->next = NULL;
		new->prev = NULL;
		return ;
	}
	temp = *lst;
	last = ft_listlast(temp);
	last->next = new;
	new->prev = last;
}
