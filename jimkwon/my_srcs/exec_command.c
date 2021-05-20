#include "minishell.h"

//echo -> abc -> aa or   pwd -> 등의 단일 커맨드와 arg가 들어온다.
void		exec_command(t_line *line)
{
	char	*command;

	command = line->arg;
	if (ft_strcmp(command, "echo") == 0)
		ft_echo(line->next);
	else if (ft_strcmp(command, "cd") == 0)
		exec_cd(line->next);
	else if (ft_strcmp(command, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(command, "export") == 0)
		exec_export(line->next);
	else if (ft_strcmp(command, "unset") == 0)
		exec_unset(line->next);
	else if (ft_strcmp(command, "env") == 0)
		exec_env(line->next);
	else if (ft_strcmp(command, "exit") == 0)
		exit(0);
	else 
		other_command(line);
}