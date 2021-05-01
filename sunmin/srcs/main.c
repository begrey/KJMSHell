/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:39:43 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/01 14:00:53 by sunmin           ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**command_line;
	int		i;

	if (argc != 1)											// 쉘에서 bash aa 이런 식으로 배쉬를 실행할 때
	{
		write(1, "cannot excute binary file\n", 26);
		return (0);
	}
	init_env(envp);
	write(1, "KJMSHell(•ө•) >> ", 22);
	while((parse_line(&line)) > 0)						// 방향키(왼, 위, 오, 아) 들어올 때 처리해야 함
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
	return (0);


	//
	argc = 1;
	argv = NULL;
	envp = NULL;
}

