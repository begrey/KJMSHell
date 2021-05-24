/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:28:27 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/21 12:46:25 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(t_line *line)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	//-nnnnn 옵션 플래그 검사kk
	if (line->arg[0] == '-' && line->arg[1] == 'n')
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

}
