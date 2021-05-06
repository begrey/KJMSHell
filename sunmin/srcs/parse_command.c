#include "minishell.h"

char  *parse_command(char *line_piece, char *str)
{
	char	**command_line;
	char	*command;
	char	*pipe_arg;
	int		len;

	pipe_arg = 0;
	str = "\0";
	command_line = ft_split(line_piece, ' ');
	command = command_line[0];
	len = 0;
	while (command_line[len])
		len++;
	if (ft_strcmp(command, "echo") == 0)
		pipe_arg = ft_echo(line_piece + 5);
	else if (ft_strcmp(command, "cd") == 0)
	{
		pipe_arg = exec_cd(command_line);
	}
	else if (ft_strcmp(command, "pwd") == 0)
	{
		pipe_arg = exec_pwd();
		pipe_arg = ft_strjoin(pipe_arg, "\n");
	}
	else if (ft_strcmp(command, "export") == 0)
	{
		pipe_arg = exec_export(command_line, len);
	}
	else if (ft_strcmp(command, "unset") == 0)
	{
		pipe_arg = exec_unset(command_line, len);
	}
	else if (ft_strcmp(command, "env") == 0)
	{
		pipe_arg = exec_env(command_line, len);
	}
	else if (ft_strcmp(command, "exit") == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	// else if (ft_strchr("<>|;", command[0]) != NULL)
	// 	parse_token(split_line, i);	
	else
		other_command(command_line);
	free_split(&command_line);
	return (pipe_arg);
}
