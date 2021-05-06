/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:10:01 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/05 11:24:23 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**check_string(char **command_line)		// 재귀함수 사용
{
	char	**result;
	char	check[4096];
	int		i;

	i = 0;
	while (i < 4096)
	{
		check[i] = 0;
		i++;
	}
	i = 1;
	while (command_line[i])
	{
		if (command_line[i][0] == '>')
		{
			check[i] = 1;
		}
		i++;
	}
	
	result = NULL;
	return (result);
}
