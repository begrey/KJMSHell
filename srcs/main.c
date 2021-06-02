/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:09:15 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/02 17:42:10 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (g_line[0] != 0)
			{
				free(g_line);
				g_line = ft_strdup("");
			}
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

void		init(t_env **env, char **list, t_list **history)
{
	*env = NULL;
	*list = NULL;
	*history = NULL;
	init_g_line();
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGQUIT, signal_handler);
	write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
}

int			main(int argc, char **argv, char **envp)
{
	t_list	*history;
	t_env	*env;
	int		read;
	char	*list;

	if (argc != 1)
	{
		write(1, "cannot excute binary file\n", 26);
		return (126);
	}
	init(&env, &list, &history);
	env = init_env(envp, env);
	while ((read = parse_line(history, env)) > 0)
	{
		list = ft_strdup(g_line);
		list[ft_strlen(list) - 1] = '\0';
		ft_lstadd_back(&history, ft_lstnew(list));
		make_list(env);
		write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
		set_signal_return(env);
		free(g_line);
		init_g_line();
	}
	return (return_return(env));
	argv = NULL;
}
