/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 11:21:53 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/05 11:26:58 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_pwd(void)
{
	char	*current_path;
	char	*buf;

	buf = NULL;
	current_path = getcwd(buf, 1);
//	free(current_path);		????
	return (current_path);
}

char	*exec_cd(char **command_line)
{
	int		check;
	char	*str;

	str = ft_strdup("");
	check = 0;
	check = chdir(command_line[1]);
	if (check == 0)
	{
		return (str);
	}
	else
	{
		str = str_append1(str, "cd: ");
		str = str_append1(str, command_line[1]);
		str = str_append1(str, ": No such file or directory\n");
	}
	return (str);
}
