#include "minishell.h"

//echo -> abc -> aa or   pwd -> 등의 단일 커맨드와 arg가 들어온다.
void		exec_command(t_line *line, char *file_name, t_env *env)
{
	char	*command;

	command = line->arg;
	if (ft_strcmp(command, "echo") == 0)
		ft_echo(line->next);
	else if (ft_strcmp(command, "cd") == 0)
		ft_cd(line->next, env);
	else if (ft_strcmp(command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command, "export") == 0)
		exec_export(line, env);
	else if (ft_strcmp(command, "unset") == 0)
		exec_unset(line, env);
	else if (ft_strcmp(command, "env") == 0)
		exec_env(line, env);
	else if (ft_strcmp(command, "exit") == 0)
		exit(10); //프로세스만 종료되기 때문에 수정 필요
	else if (ft_strcmp(command, "") == 0)
		exit(0); //$! 관련으로 차후에 수정 status
	else 
		other_command(line, env);
	file_name = NULL;
}
