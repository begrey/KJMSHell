/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:09:15 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/08 10:36:16 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char **argv, char **envp)
{
	t_prompt	*prom;
	t_env		*env;
	int			read;
	char		*list;

	if (argc != 1 && ft_strlen(argv[0]) != 0)
	{
		write(1, "cannot excute binary file\n", 26);
		return (126);
	}
	init(&env, &list, &prom);
	env = init_env(envp, env);
	while ((read = input_line(prom, env, 0)) > 0)
	{
		list = ft_strdup(g_line);
		list[ft_strlen(list) - 1] = '\0';
		ft_hisadd_back(&(prom->history), ft_hisnew(list));
		make_list(env);
		if (g_line[0] != -3)
			write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
		set_signal_return(env);
		free(g_line);
		init_g_line();
	}
	return (return_return(env));
}
