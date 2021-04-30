/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:39:43 by jimkwon           #+#    #+#             */
/*   Updated: 2021/04/30 14:12:21 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_pipes(char *command_line)
{
	char **pipe_line;
	char *str;
	int i;

	i = 0;
	pipe_line = ft_split(command_line, '|');
	while(pipe_line[i] != NULL)
	{
		str = parse_command(pipe_line[i], str);
		i++;
	}
	write(1, str, ft_strlen(str));
}

int main() // int argc, char **argv, char **envp gcc플래그 오류로 잠시 주석처리해둠, 아직 사용 x
{
	char	*line;
	char	**command_line;
	int		i;

	write(1, "KJMSHell(•ө•) >> ", 22);
	while((parse_line(&line)) > 0)
	{
		i = 0;
		command_line = ft_split(line, ';');
		while(command_line[i] != NULL)
		{
			split_pipes(command_line[i]);
			i++;
		}
		write(1, "KJMSHell(•ө•) >> ", 22);
	}
	
	write(1, "parseError!\n", 12);
}

