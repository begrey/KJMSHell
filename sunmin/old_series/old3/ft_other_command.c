#include "minishell.h"

void	other_command(t_line **command_line)		// /bin/ls 이런 식으로 명령어가 들어올 때도 실행되도록 해야 함
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
		single_line = str_append2(single_line, (temp)->arg);
		temp = (temp)->next;
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
		if (errno)
		{
			char *str = strerror(errno);
			int	failure;
			failure = 0;
			if (errno == 2)
			{
				failure = 127;
			}
			else
				failure = 1;
			printf("%s\n", str);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, status, 0);
	}
}
