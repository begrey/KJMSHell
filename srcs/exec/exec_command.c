/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:43:46 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/04 16:23:56 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			if_empty_string(t_line *line,
		int pip_flag, t_env *env)
{
	if (ft_strcmp(line->arg, "\"\"") == 0
			|| ft_strcmp(line->arg, "\'\'") == 0)
	{
		printf(" : command not found\n");
		if (pip_flag == 0)
			exit(127);
		else
		{
			put_return(127, env);
			return (1);
		}
	}
	return (0);
}

void		exec_command(t_line *line, char *file_name,
t_env *env, int pip_flag)
{
	char	*command;

	if (line == NULL)
		return ;
	if ((if_empty_string(line, pip_flag, env)) == 1)
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
