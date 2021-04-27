/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSHell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 09:58:10 by sunmin            #+#    #+#             */
/*   Updated: 2021/04/27 20:35:29 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./MsHell.h"

int		main(int argc, char **argv, char **envp)
{
	char	*raw_line;
	char	**split_specifier;
	char	*command;
	char	*option;
	char	*string;
	char	buf;
	char	path_buf[4096];
	int		read_n;
	char	*current_path;
	int		num;
	char	key;
	int		i;
	char	***split_line;

	while (1)
	{
		current_path = getcwd(path_buf, 100);
		write(1, "MSHell ", 7);
		write(1, current_path, ft_strlen(current_path));
		write(1, "## ", 3);

		get_next_line(0, &raw_line);
		if ((num = ft_find(raw_line, ';') + 1))
		{
			key = ';';
			split_specifier = ft_split(raw_line, key);
		}
		split_line = (char ***)malloc(sizeof(char **) * (num + 1));
		split_line[num] = NULL;
		i = 0;
		while (i < num)
		{
			split_line[i] = ft_split(split_specifier[i], ' ');
			i++;
		}
		i = 0;
		while (i < num)
		{
			command = split_line[i][0];
			if (ft_strncmp(command, "exit", 4) == EQUAL)
			{
				write(1, "bye\n", 4);
				return (0);
			}
			else if (ft_strncmp(command, "pwd", 3) == EQUAL)
			{
				write(1, current_path, ft_strlen(current_path));
				write(1, "\n", 1);
			}
			else
			{
				write(1, "command not found\n", 18);
			}
			i++;
		}
	}
	return (0);
}
