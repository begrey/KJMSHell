/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:28:27 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/19 13:16:30 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(t_line *line)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	//-nnnnn 옵션 플래그 검사
	if (line->arg[0] == '-' && line->arg[1] == 'n')
	{
		flag = 1;
		while (line->arg[i] != '\0')
			if (line->arg[i] != 'n')
				flag = 0;
		line = line->next;
	}
	while (line != NULL)
	{
		printf("%s", line->arg);
		if (line->next != NULL)
			printf(" ");
		line = line->next;
	}
}
