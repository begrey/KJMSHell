/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:35:47 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/14 20:02:59 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*delete;
	t_list	*prev;

	temp = *lst;
	prev = temp;
	if (temp == NULL)
		return ;
	while (prev != ft_lstlast(temp))
	{
		while (prev->next != ft_lstlast(temp))
			prev = prev->next;
		delete = prev->next;
		ft_lstdelone(delete, (*del));
		prev->next = NULL;
	}
	ft_lstdelone(prev, (*del));
	*lst = NULL;
}
