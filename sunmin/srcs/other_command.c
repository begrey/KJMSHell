/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:46:38 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/04 13:25:02 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// 결과값 str을 리턴받아서 이어붙이는 식인데, 다른 명령어들도 그런 식으로 되어있지 않으면 구조를 바꾸어야 함 

char	*other_command(char **command_line, int len)
{
//	c_l = "ls abc" len = "2"
	int		i;
	char	*str;
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
			new_path = ft_strjoin(split_path[i], "/");
			new_path = ft_strjoin(new_path, command_line[0]);		// new_path = "/user/bin/ls"
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

	len = 1;
	command_line = NULL;
	str = NULL;
}
