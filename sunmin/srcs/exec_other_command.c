#include "minishell.h"

void	other_command(t_line **command_line)
{
	int		i;
	char	*path;
	char	**split_path;
	char	*new_path;
	pid_t	pid;
	int		*status;
	char	*single_line;
	t_line	*temp;

	temp = *command_line;

	single_line = ft_strdup("");
	while (temp)
	{
		single_line = str_append2(single_line, temp->arg);
		temp = temp->next;
	}

	status = NULL;
	pid = fork();
	if (pid == 0)
	{
		path = extract_env("$PATH");
		split_path = ft_split(path, ':');
		i = 0;
		while (split_path[i])	// 환경변수에서 PATH경로 찾아서 찾음
		{
			new_path = ft_strdup("");
			new_path = str_append1(split_path[i], "/");
			new_path = str_append1(new_path, (*command_line)->arg);		// new_path = "/user/bin/ls"
			execve(new_path, &single_line, NULL);
			i++;
		}
		printf("%s: command not found\n", (*command_line)->arg);
	}
	else
	{
		waitpid(pid, status, 0);
	}
}
