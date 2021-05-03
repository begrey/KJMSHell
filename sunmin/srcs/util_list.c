/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:31:13 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/03 09:04:58 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_listnew(void *key, void *value)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->key = key;
	new->value = value;
	return (new);
}

void	ft_listadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	last = ft_listlast(*lst);
	last->next = new;
	new->next = (NULL);
}

t_env	*ft_listlast(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->next)
			lst = lst->next;
		else
			break;
	}
	return (lst);
}

t_env	*ft_listfind(t_env **lst, char *s)
{
	t_env *begin;

	begin = *lst;
	while (begin)
	{
		if ((ft_strcmp(begin->key, s)) == 0)
			return (begin);
		begin = begin->next;
	}
	return NULL;
}
