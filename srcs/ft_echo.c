/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:28:27 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/02 12:03:10 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_n_flag(t_line *line)
{
	int		flag;
	int		i;

	i = 1;
	flag = 0;
	if (line && line->arg[0] == '-' && line->arg[1] == 'n')
	{
		flag = 1;
		while (line->arg[++i] != '\0')
			if (line->arg[i] != 'n')
				flag = 0;
	}
	return (flag);
}

void		ft_echo(t_line *line, int pip_flag, t_env *env)
{

	int		flag;

	flag = find_n_flag(line);
	if (flag == 1)
		line = line->next;
	while (line != NULL)
	{
		write(1, line->arg, ft_strlen(line->arg));
		if (line->next != NULL)
			write(1, " ", 1);
		line = line->next;
	}
	if (flag == 0)
		write(1, "\n", 1);
	if (pip_flag == 0)
		exit(0);
	else
		put_return(0, env);
	printf("hello\n");
}
