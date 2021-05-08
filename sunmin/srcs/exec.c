#include "minishell.h"

void		ft_exec(t_line **command_line)
{
	if (ft_strcmp((*command_line)->arg, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp((*command_line)->arg, "cd") == 0)
		exec_cd(command_line);
	else if (ft_strcmp((*command_line)->arg, "echo") == 0)
		;
	else if (ft_strcmp((*command_line)->arg, "export") == 0)
		exec_export(command_line);
	else if (ft_strcmp((*command_line)->arg, "unset") == 0)
		exec_unset(command_line);
	else if (ft_strcmp((*command_line)->arg, "env") == 0)
		exec_env(command_line);
	else if (ft_strcmp((*command_line)->arg, "exit") == 0)
		;
	else
		;
//		other_command(command_line);
}
