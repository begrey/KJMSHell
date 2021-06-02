/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:36:46 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/02 17:42:23 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					num_len(int n)
{
	int				i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
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

int					putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
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

int					remove_c(t_cursor *cursor)
{
	char			*str;
	int				i;

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

int					append(char c)
{
	char			*str;
	int				i;

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

void				term_off(struct termios term)
{
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

struct termios		term_on(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (term);
}

void				init_cursor_term(t_cursor *cursor,
struct termios *term, int *h_cnt)
{
	tgetent(NULL, "xterm");
	cursor->cm = tgetstr("cm", NULL);
	cursor->ce = tgetstr("ce", NULL);
	cursor->max_col = 0;
	cursor->prev_col = 0;
	cursor->last_col_flag = 0;
	*term = term_on();
	*h_cnt = 0;
}

int					put_cursor(t_cursor *cursor, struct termios term, char c)
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

int				check_c(t_list *history, int *h_cnt, t_cursor *cursor, int c)
{
	if (c == 4)
	{
		if ((int)g_line[0] == 4)
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

void				set_sigint_env(t_env *env)
{
	put_return(1, env);
	g_line[0] = 0;
}

int						parse_line(t_list *history, t_env *env)
{
	struct termios		term;
	int					c;
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
			if ((status = check_c(history, &h_cnt, &cursor, c)) >= -1)
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
