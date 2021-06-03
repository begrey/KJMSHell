/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:09:15 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:00:31 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while ((read = input_line(history, env, 0)) > 0)
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
