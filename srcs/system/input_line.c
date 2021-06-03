/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:36:46 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:03:06 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						remove_c(t_cursor *cursor)
{
	char				*str;
	int					i;

	i = 0;
	if (ft_strlen(g_line) == 0)
	{
		g_line[0] = 0;
		return (0);
	}
	if (cursor->last_col_flag == 1 && (cursor->col + 1) == cursor->max_col)
	{
		g_line[ft_strlen(g_line) - 1] = '\0';
		cursor->last_col_flag = 0;
	}
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(g_line))))
		return (-1);
	while (i != (int)ft_strlen(g_line) - 1)
	{
		str[i] = g_line[i];
		i++;
	}
	str[i] = 0;
	free(g_line);
	g_line = str;
	return (0);
}

int						append(char c)
{
	char				*str;
	int					i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(g_line) + 2))))
		return (-1);
	while (g_line[i] != '\0')
	{
		str[i] = g_line[i];
		i++;
	}
	str[i] = c;
	i++;
	str[i] = 0;
	free(g_line);
	g_line = str;
	return (0);
}

int						put_cursor(t_cursor *cursor,
struct termios term, char c)
{
	cursor->prev_col = cursor->col;
	write(1, &c, 1);
	get_cursor_position(cursor);
	if (cursor->col == cursor->prev_col)
		cursor->last_col_flag = 1;
	if (cursor->max_col <= cursor->col)
		cursor->max_col = cursor->col;
	if ((append((char)c)) == -1)
		return (0);
	if ((char)c == '\n')
	{
		term_off(term);
		return (1);
	}
	if (!g_line)
		return (0);
	return (-1);
}

int						check_c(t_list *history,
int *h_cnt, t_cursor *cursor, int c)
{
	if (c == 4)
	{
		if ((int)ft_strlen(g_line) == 0)
		{
			printf("exit\n");
			return (-1);
		}
	}
	if (c == U_ARROW)
		*h_cnt = find_history(history, *h_cnt + 1, cursor);
	else if (c == D_ARROW)
		*h_cnt = find_history(history, *h_cnt - 1, cursor);
	else if (c == BACKSPACE)
	{
		delete_end(cursor);
		if ((remove_c(cursor)) == -1)
			return (0);
	}
	return (-9);
}

int						input_line(t_list *history, t_env *env, int c)
{
	struct termios		term;
	int					h_cnt;
	int					status;
	t_cursor			cursor;

	init_cursor_term(&cursor, &term, &h_cnt);
	get_cursor_position(&cursor);
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (g_line[0] == -3)
			set_sigint_env(env);
		if (c == U_ARROW || c == D_ARROW || c == BACKSPACE || c == 4)
		{
			if ((status = check_c(history, &h_cnt, &cursor, c)) == -1)
				return (-1);
		}
		else if (c != L_ARROW && c != R_ARROW)
		{
			if ((status = put_cursor(&cursor, term, c)) >= 0)
				return (status);
			renew_history(history, h_cnt);
		}
		c = 0;
	}
	return (-1);
}
