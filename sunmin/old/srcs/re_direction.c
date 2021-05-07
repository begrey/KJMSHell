/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:10:01 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/07 15:41:30 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*path_address(char *line)
{
	char	*address;

	address = ft_strjoin("./", line);
	return (address);
}

char	*redir_command(char *command_line, char* str)		// 재귀함수 사용
{
	int		i;
	char	**redir_line;
	char	*redir_command_line;
	int		len;
//	int		fd;
//	pid_t	pid;

	redir_line = parse_redir(command_line);
	len = split_len(redir_line);
	redir_command_line = (char *)malloc(sizeof(char) * 1);
	redir_command_line[0] = '\0';
	redir_command_line = str_append2(redir_command_line, redir_line[0]);
	redir_command_line = str_append1(redir_command_line, " ");
	redir_command_line = str_append2(redir_command_line, redir_line[1]);

	i = 2;
	while (redir_line[i])		// 마지막꺼만 echo를 실행시키고 나머지는 단순히 >a 한것처럼
	{
		pid = fork();
		if (pid != 0)
			waitpid(pid, 0, 0);
		if (pid == 0)
		{
			redir_line[i] = path_address(redir_line[i]);
			fd = open(redir_line[i], O_CREAT | O_TRUNC | O_RDWR, 00777);
			dup2(1, temp_fd);
			dup2(fd, 1);
			if (i == len - 1)
			{
				str = parse_command(redir_command_line, str);
			}
			i++;
		}
	}
	return (str);
}

char	**parse_redir(char *command_line)
{
	char	**split_redir;
	char	**temp;
	int		arg_len = 0;
	int		i;
	int		j;
	int		flag = 0;

	temp = ft_split(command_line, ' ');
	while (temp[arg_len])
		arg_len++;
	split_redir = (char **)malloc(sizeof(char *) * (arg_len + 1));
	split_redir[arg_len] = NULL;
	i = 0;
	while (i < arg_len)
	{
		j = 0;
		while (temp[j])
		{
			if ((ft_strchr(temp[j], '>') == NULL) && flag < 2)
			{
				split_redir[i] = ft_strdup(temp[j]);
				flag++;
				i++;
			}
			if ((ft_strchr(temp[j], '>') != NULL) && flag >= 2)
			{
				split_redir[i] = ft_strdup(temp[j] + 1);
				i++;
			}
			j++;
		}
	}
	i = 0;
	return (split_redir);
}
