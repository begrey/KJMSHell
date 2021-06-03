/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:51:58 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:22:34 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void				set_cursor_row_col(t_cursor *cursor, char *buf)
{
	int				a;
	int				temp;

	a = 0;
	while (*buf)
	{
		if (*buf >= '0' && *buf <= '9')
		{
			if (a == 0)
			{
				cursor->row = atoi(buf) - 1;
				buf += num_len(cursor->row);
			}
			else
			{
				temp = atoi(buf) - 1;
				cursor->col = temp;
				break ;
			}
			a++;
		}
		buf++;
	}
}

void				get_cursor_position(t_cursor *cursor)
{
	char			*buf;
	int				ret;

	buf = (char *)malloc(sizeof(char) * 255);
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	set_cursor_row_col(cursor, buf);
	free(buf);
}

void				delete_end(t_cursor *cursor)
{
	get_cursor_position(cursor);
	if ((int)ft_strlen(g_line) == 0)
		return ;
	--(cursor->col);
	if (cursor->col == -1)
	{
		cursor->row--;
		cursor->col = cursor->max_col - 1;
	}
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}

void				delete_line(t_cursor *cursor)
{
	int				len;

	get_cursor_position(cursor);
	len = cursor->col - 19;
	if (cursor->col < 0)
		cursor->col = 0;
	tputs(tgoto(cursor->cm, cursor->col - len, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}
