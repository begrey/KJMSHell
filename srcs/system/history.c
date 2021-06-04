/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:54:21 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/04 13:15:10 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					adjust_cnt(t_his *history,
int cnt, t_cursor *cursor, char *origin_line)
{
	if (cnt <= 0)
	{
		delete_line(cursor);
		free(g_line);
		g_line = ft_strdup(origin_line);
		write(1, g_line, ft_strlen(g_line));
		return (0);
	}
	else if (cnt > ft_hissize(history))
	{
		cnt = ft_hissize(history);
		return (cnt);
	}
	return (-1);
	printf("%d\n", cursor->col);
}

int					find_history(t_prompt *prom, int cnt, t_cursor *cursor)
{
	t_his			*temp;
	int				len;
	int				i;

	if (prom->history == NULL)
		return (0);
	if ((i = adjust_cnt(prom->history, cnt, cursor, prom->origin_line)) >= 0)
		return (i);
	temp = prom->history;
	i = 1;
	len = ft_hissize(prom->history) - cnt + 1;
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

void				renew_history(t_his *history, int cnt)
{
	t_his			*temp;
	int				len;
	int				i;

	if (history == NULL || cnt <= 0)
		return ;
	temp = history;
	i = 1;
	len = ft_hissize(history) - cnt + 1;
	while (temp != NULL && i != len)
	{
		temp = temp->next;
		i++;
	}
	free(temp->content);
	temp->content = ft_strdup(g_line);
}

void				restore_history(t_his *history, int cnt)
{
	t_his			*temp;
	int				len;
	int				i;

	if (history == NULL)
		return ;
	if (cnt <= 0)
		return ;
	temp = history;
	i = 1;
	len = ft_hissize(history) - cnt + 1;
	while (temp != NULL && i != len)
	{
		temp = temp->next;
		i++;
	}
	free(temp->content);
	temp->content = ft_strdup(temp->prev_his);
}

void				free_origin_line(t_prompt *prom)
{
	free(prom->origin_line);
	prom->origin_line = ft_strdup(g_line);
}
