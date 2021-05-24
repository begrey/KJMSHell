#include "minishell.h"

//echo -> abc -> aa or   pwd -> 등의 단일 커맨드와 arg가 들어온다.
void		exec_command(t_line *line, char *file_name)
{
	char	*command;

	command = line->arg;
	if (ft_strcmp(command, "echo") == 0)
		ft_echo(line->next);
	else if (ft_strcmp(command, "cd") == 0)
		ft_cd(line->next);
	else if (ft_strcmp(command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command, "export") == 0)
		exec_export(line);
	else if (ft_strcmp(command, "unset") == 0)
		exec_unset(line);
	else if (ft_strcmp(command, "env") == 0)
		exec_env(line);
	else if (ft_strcmp(command, "exit") == 0)
		exit(0); //프로세스만 종료되기 때문에 수정 필요
	else if (line->arg[0] == '\0')
		return ;
	else 
		other_command(line);
	file_name = NULL;
}
