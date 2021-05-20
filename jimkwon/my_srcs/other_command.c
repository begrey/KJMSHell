/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:46:38 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/19 14:02:03 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	make_argv(char	**argv, t_line *line)
{
	int	i;

	i = 0;
	while (line != NULL)
	{
		*argv[i] = line->arg;
		line = line->next;
		i++;
	}
}

char	*other_command(t_line *line)
{
	int		i;
	char	*str;
	char	*path;
	char	**split_path;
	char	*new_path;
	pid_t	pid;
	int		status;
	char	**argv;
	char	**const envp;

	envp[] = {NULL};
	status = 0;
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
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		//printf("errno: %s\n", strerror(errno));
	}
	return NULL;

	len = 1;
	command_line = NULL;
	str = NULL;
}
