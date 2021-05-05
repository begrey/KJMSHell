/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:46:38 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/05 09:27:23 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*other_command(char **command_line)
{
	int		i;
	char	*path;
	char	**split_path;
	char	*new_path;
	pid_t	pid;
	int		*status;

	status = NULL;
	pid = fork();
	if (pid == 0)
	{
		path = extract_env("$PATH");
		split_path = ft_split(path, ':');
		i = 0;
		while (split_path[i])	// 환경변수에서 PATH경로 찾아서 찾음
		{
			new_path = ft_strdup("");
			new_path = str_append1(split_path[i], "/");
			new_path = str_append1(new_path, command_line[0]);		// new_path = "/user/bin/ls"
			execve(new_path, command_line, NULL);
			i++;
		}
		printf("%s: command not found\n", command_line[0]);
	}
	else
	{
		waitpid(pid, status, 0);
	}
	return NULL;
}
