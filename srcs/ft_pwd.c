/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 11:21:53 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/03 12:15:28 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_pwd(void)
{
	char	*current_path;
	char	*buf;

	buf = NULL;
	current_path = getcwd(buf, 100);
	return (current_path);
}

char	*exec_cd(char **command_line)
{
	int		check;
	char	*str;

	str = NULL;
	if (!str)
		str = ft_strdup("");
	check = 0;
	check = chdir(command_line[1]);
	if (check == 0)
	{
		return (str);
	}
	else
	{
		str = ft_strjoin(str, "cd: ");
		str = ft_strjoin(str, command_line[1]);
		str = ft_strjoin(str, ": No such file or directory\n");
	}
	return (str);
}
