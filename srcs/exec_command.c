#include "minishell.h"

//echo -> abc -> aa or   pwd -> 등의 단일 커맨드와 arg가 들어온다.
void		exec_command(t_line *line, char *file_name, t_env *env, int pip_flag)
{
	char	*command;

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
		ft_exit(line->next, env, pip_flag); //프로세스만 종료되기 때문에 수정 필요
	else if (ft_strcmp(command, "") == 0)
		;
	else 
		other_command(line, env, file_name, pip_flag);
}
