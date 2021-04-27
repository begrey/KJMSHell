/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSHell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 09:58:10 by sunmin            #+#    #+#             */
/*   Updated: 2021/04/27 11:25:00 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./MsHell.h"

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_append(char *line, char buf)
{
	int		i;
	char	*result;

	if (!(result = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
		return NULL;
	i = 0;
	while (line[i])
	{
		result[i] = line[i];
		i++;
	}
	result[i] = buf;
	i++;
	result[i] = '\0';
	free(line);
	return (result);
}

int		main(int argc, char **argv, char **envp)
{
	char	*one_line;
	char	buf;
	char	path_buf[4096];
	int		read_n;
	char	*current_path;

	while (1)
	{
		current_path = getcwd(path_buf, 100);
		write(1, "MSHell# ", 8);							// write 대신 printf를 사용하면 바로 출력 안됨 
		write(1, current_path, ft_strlen(current_path));
		write(1, " ", 1);
		while ((read_n = read(0, &buf, 1)) > 0)
		{
			if (buf == '\n')
				continue;
//				split_command();
		}
	}
	return (0);
}
