/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSHell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 09:58:10 by sunmin            #+#    #+#             */
/*   Updated: 2021/04/27 19:27:38 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ctrl + d -> sanitizer error

#include "./MsHell.h"

int		main(int argc, char **argv, char **envp)
{
	char	*raw_line;
	char	**split_line;
	char	*command;
	char	*option;
	char	*string;
	char	buf;
	char	path_buf[4096];
	int		read_n;
	char	*current_path;

	while (1)
	{
		current_path = getcwd(path_buf, 100);

		write(1, "MSHell ", 7);
		write(1, current_path, ft_strlen(current_path));
		write(1, "## ", 3);

		get_next_line(0, &raw_line);
		split_line = ft_split(raw_line , ' ');
		command = split_line[0];

		if (ft_find(command, ';') == EXIST)
		{
			write(1, "wet\n", 4);
		}
		else if (ft_find(command, '\'') == EXIST || ft_find(command, '\"') == EXIST)
		{
			write(1, "one eye\n", 8);
		}
		else if (ft_find(command, '<') == EXIST || ft_find(command, '>') == EXIST)
		{
			write(1, "shy ><\n", 7);
		}
		else if (ft_find(command, '|') == EXIST)
		{
			write(1, "nose\n", 5);
		}
		else
		{
			if ((ft_strncmp(command, "echo", 4) == EQUAL))		// 만약 여기다 jimkwon/echo.c 를 연동한다고 하면
				break;
			else if ((ft_strncmp(command, "cd", 2) == EQUAL))
				break;
			else if ((ft_strncmp(command, "ls", 2) == EQUAL))
				break;
			else if ((ft_strncmp(command, "pwd", 3) == EQUAL))
				break;
			else if ((ft_strncmp(command, "export", 6) == EQUAL))
				break;
			else if ((ft_strncmp(command, "unset", 5) == EQUAL))
				break;
			else if ((ft_strncmp(command, "env", 3) == EQUAL))
				break;
			else if ((ft_strncmp(command, "exit", 4) == EQUAL))
				break;
			else	
				write(1, "command not found\n", 18);
		}
	}
	return (0);
}
