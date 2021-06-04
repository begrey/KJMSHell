/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:56:21 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/04 09:05:41 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void				set_sigint_env(t_env *env)
{
	put_return(1, env);
	g_line[0] = 0;
}
