/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:54:21 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:22:39 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					adjust_cnt(t_list *history, int cnt, t_cursor *cursor)
{
	if (cnt <= 0)
	{
		delete_line(cursor);
		free(g_line);
		g_line = ft_strdup("");
		return (0);
	}
	else if (cnt > ft_lstsize(history))
	{
		cnt = ft_lstsize(history);
		return (cnt);
	}
	return (-1);
}

int					find_history(t_list *history, int cnt, t_cursor *cursor)
{
	t_list			*temp;
	int				len;
	int				i;

	if (history == NULL)
		return (0);
	if ((i = adjust_cnt(history, cnt, cursor)) >= 0)
		return (i);
	temp = history;
	i = 1;
	len = ft_lstsize(history) - cnt + 1;
	while (temp != NULL && i != len)
	{
		temp = temp->next;
		i++;
	}
	delete_line(cursor);
	write(1, temp->content, ft_strlen(temp->content));
	free(g_line);
	g_line = ft_strdup(temp->content);
	return (cnt);
}

void				renew_history(t_list *history, int cnt)
{
	t_list			*temp;
	int				len;
	int				i;

	if (history == NULL || cnt <= 0)
		return ;
	temp = history;
	i = 1;
	len = ft_lstsize(history) - cnt + 1;
	while (temp != NULL && i != len)
	{
		temp = temp->next;
		i++;
	}
	free(temp->content);
	temp->content = ft_strdup(g_line);
}
