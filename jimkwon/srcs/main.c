/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:39:43 by jimkwon           #+#    #+#             */
/*   Updated: 2021/04/30 02:09:05 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main() // int argc, char **argv, char **envp gcc플래그 오류로 잠시 주석처리해둠, 아직 사용 x
{
	char	*line;
	char	**split_line;
	char	*command;
	int		i;

	i = 0;
	write(1, "KJMSHell(•ө•) >> ", 22);
	parse_line(&line);
	split_line = ft_split(line, ' ');
	while (1)
	{
		command = split_line[i];
		if (ft_strcmp(command, "echo") == 0)
			printf("echo 명령어입니다.\n");
		else if (ft_strcmp(command, "cd") == 0)
			printf("cd 명령어입니다.\n");
		else if (ft_strcmp(command, "pwd") == 0)
			printf("pwd 명령어입니다.\n");
		else if (ft_strcmp(command, "export") == 0)
			printf("export 명령어입니다.\n");
		else if (ft_strcmp(command, "unset") == 0)
			printf("unset 명령어입니다.\n");
		else if (ft_strcmp(command, "env") == 0)
			printf("env 명령어입니다.\n");
		else if (ft_strcmp(command, "exit") == 0)
			exit(0);
		else if (ft_strchr("<>|;", command[0]) != NULL)
			parse_token(split_line, i);
		else
			printf("%s: command not found\n", command);
		i++;
		if (split_line[i] == NULL) //한 줄이 끝나고 다음 줄을 기다린다.
		{
			write(1, "KJMSHell(•ө•) >> ", 22);
			i = 0;
			parse_line(&line);
			split_line = ft_split(line, ' ');
		}
	}
	write(1, "parseError!\n", 12);
}

