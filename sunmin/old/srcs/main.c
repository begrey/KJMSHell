#include "minishell.h"

void	split_pipes(char *command_line)
{
	char **pipe_line;
	char *str;
	int i;

	i = 0;
	pipe_line = ft_split(command_line, '|');

//	while(pipe_line[i] != NULL)		원본
//	{
//		str = parse_command(pipe_line[i], str);
//		i++;
//	}


//	int	strout;

	while(pipe_line[i] != NULL)
	{
		str = redir_command(pipe_line[i], str);
		i++;
	}
/*
	while (redir)
	{
		if (strout = open(""))
		{

		}
		else
*/
		if (str)
			write(fd, str, ft_strlen(str));
//	}
}

int main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**command_line;
	int		i;

	if (argc != 1)											// 쉘에서 bash aa 이런 식으로 배쉬를 실행할 때
	{
		write(1, "cannot excute binary file\n", 26);
		return (0);
	}
	init_env(envp);
	write(1, "KJMSHell(•ө•) >> ", 22);
	while((parse_line(&line)) > 0)						// ctrl + c 누르면 종료됨, 배쉬는 아님
	{
		i = 0;
		command_line = ft_split(line, ';');
		while(command_line[i] != NULL)
		{
			split_pipes(command_line[i]);
			i++;
		}
		dup2(temp_fd, 1);	// 이걸 안해주면 리다이렉션 폴더에 "KJMSHell(OoO)"가 같이 담김
		write(1, "KJMSHell(•ө•) >> ", 22);
		free(line);										// 메모리 누수 때문에 추가
	}
	write(1, "parseError!\n", 12);			// ctrl + d로 종료하면 뜸
	return (0);

	argv[1] = (char *)1;
}
