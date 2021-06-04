/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:00:13 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/04 13:34:58 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		signal_sigquit(int sig)
{
	if (ft_strchr(g_line, '\n') != NULL)
	{
		g_line[0] = -2;
		printf("Quit: %d\n", sig);
	}
}

void		signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (ft_strchr(g_line, '\n') != NULL)
		{
			g_line[0] = -1;
			printf("\n");
		}
		else
		{
			if (g_line[0] != -3 && ft_strlen(g_line))
			{
				free(g_line);
				g_line = ft_strdup("");
				g_line[0] = -3;
			}
			else
				g_line[0] = -3;
			write(1, "\nKJMSHell(｡☌ᴗ☌｡) >> ", 30);
		}
	}
	if (sig == SIGQUIT)
		signal_sigquit(sig);
}

void		set_signal_return(t_env *env)
{
	if (g_line[0] == -1)
		put_return(130, env);
	else if (g_line[0] == -2)
		put_return(131, env);
}

void		init_g_line(void)
{
	if (!(g_line = malloc(1)))
		return ;
	(g_line)[0] = 0;
}

void		init(t_env **env, char **list, t_prompt **prom)
{
	*env = NULL;
	*list = NULL;
	if (!((*prom) = (t_prompt *)malloc(sizeof(t_prompt) * 1)))
		return ;
	(*prom)->history = NULL;
	(*prom)->origin_line = ft_strdup("");
	init_g_line();
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGQUIT, signal_handler);
	write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
}
