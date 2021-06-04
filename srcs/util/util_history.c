/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 09:44:52 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/04 13:12:01 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_hissize(t_his *his)
{
	t_his		*temp;
	int			len;

	len = 0;
	temp = his;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

t_his			*ft_hislast(t_his *his)
{
	t_his		*temp;

	if (!his)
		return (NULL);
	temp = his;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_his			*ft_hisnew(void *content)
{
	t_his		*his;

	if (!(his = (t_his *)malloc(sizeof(t_his) * 1)))
		return (NULL);
	his->content = content;
	his->prev_his = ft_strdup(content);
	his->next = NULL;
	return (his);
}

void			ft_hisadd_back(t_his **his, t_his *new)
{
	t_his		*last;
	t_his		*temp;

	temp = *his;
	if (temp == NULL)
	{
		*his = new;
		new->next = NULL;
		return ;
	}
	temp = *his;
	last = ft_hislast(temp);
	last->next = new;
}
