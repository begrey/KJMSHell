/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:43:46 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/04 11:48:55 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		exec_command(t_line *line, char *file_name,
t_env *env, int pip_flag)
{
	char	*command;

	if (line == NULL)
		return ;
	command = line->arg;
	if (ft_strcmp(command, "echo") == 0)
		ft_echo(line->next, pip_flag, env);
	else if (ft_strcmp(command, "cd") == 0)
		ft_cd(line->next, env, pip_flag);
	else if (ft_strcmp(command, "pwd") == 0)
		ft_pwd(pip_flag, env);
	else if (ft_strcmp(command, "export") == 0)
		exec_export(line, env, pip_flag);
	else if (ft_strcmp(command, "unset") == 0)
		exec_unset(line, env, pip_flag);
	else if (ft_strcmp(command, "env") == 0)
		exec_env(line, env, pip_flag);
	else if (ft_strcmp(command, "exit") == 0)
		ft_exit(line->next, env, pip_flag);
	else if (ft_strcmp(command, "") == 0)
		;
	else
		other_command(line, env, file_name, pip_flag);
}
