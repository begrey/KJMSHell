/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:28:27 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/27 14:21:08 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(t_line *line, int pip_flag)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	//-nnnnn 옵션 플래그 검사kk
	if (line && line->arg[0] == '-' && line->arg[1] == 'n')
	{
		flag = 1;
		while (line->arg[++i] != '\0')
			if (line->arg[i] != 'n')
				flag = 0;
		if (flag == 1)
			line = line->next;
	}
	while (line != NULL)
	{
		write(1, line->arg, ft_strlen(line->arg));
		if (line->next != NULL)
			write(1, " ", 1);
		line = line->next;
	}
	if (flag == 0)
		write(1, "\n", 1);
	//printf("echo: %s\n", strerror(errno));
	if (pip_flag == 0) //파이프인경우
		exit(0);
}
