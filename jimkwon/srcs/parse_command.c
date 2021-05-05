/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:26:54 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/03 23:28:40 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char  *parse_command(char *line_piece, char *str)
{
	char	**command_line;
	char	*command;
	char	*pipe_arg;

	pipe_arg = 0;
	if (str[0] == 0)
		printf("aa\n");
	command_line = ft_split(line_piece, ' ');
	command = command_line[0];
	if (ft_strcmp(command, "echo") == 0)
		pipe_arg = ft_echo(line_piece + 5);
	else if (ft_strcmp(command, "cd") == 0)
		pipe_arg = ft_strdup("cd 명령어입니다.\n");
	else if (ft_strcmp(command, "pwd") == 0)
		pipe_arg = ft_strdup("pwd 명령어입니다.\n");
	else if (ft_strcmp(command, "export") == 0)
		pipe_arg = ft_strdup("export 명령어입니다.\n");
	else if (ft_strcmp(command, "unset") == 0)
		pipe_arg = ft_strdup("unset 명령어입니다.\n");
	else if (ft_strcmp(command, "env") == 0)
		pipe_arg = ft_strdup("env 명령어입니다.\n");
	else if (ft_strcmp(command, "exit") == 0)
		exit(0);
	// else if (ft_strchr("<>|;", command[0]) != NULL)
	// 	parse_token(split_line, i);	
	else
		printf("%s: command not found\n", command);
	return (pipe_arg);
}