#include "minishell.h"

void	make_env(t_line **line, char *split_line)
{
	;	// 생각보다 어려움
}

void make_list(t_line **line, char *s_line)
{
	char **split_line;
	int i;

	i = 0;
	split_line = ft_split_quote(s_line);
	while (split_line[i] != NULL)
	{
		ft_listadd_back(&(*line), ft_listnew(split_line[i]));
		i++;
	}


	i = 0;
	while (split_line[i])
	{
		split_line[i] = convert_env(split_line[i]);
		printf("line[%d] :%s\n", i, split_line[i]);
		i++;
	}
//

//	make_env(line, split_line);
}

void split_arg(t_line **line, char *arg_line) // echo c
{
	t_line *arg_list;

	arg_list = NULL;
	ft_exec(&arg_list);
	(*line)->line = arg_list;
}

void	split_redirection(t_line **line, char *redir_line)		// sunmin 만듦
{									//redir_line 으로 echo >aa >bb c 들어옴
	t_line		*redir_list;
	t_line		*temp;
	int			i;

	i = 0;
	redir_list = NULL;
	(*line)->line = redir_list;
	temp = redir_list;
//	set_redirection(line, redir_line);	// temp->arg에는 echo c 만 들어있게 됨
///	set_quote();
//	while (*((*line)->stream))		// stream배열 만큼 (redirection 개수 만큼)
	if (ft_strchr(redir_line, '>'))
	{
		stream = (char **)malloc(sizeof(char *) * 2);
		stream[0] = ft_strdup("bb");
		stream[1] = NULL;
	}
	else
	{
		stream = (char **)malloc(sizeof(char *) * 2);
		stream[0] = (char *)1;
		stream[1] = NULL;
	}
	while (*stream)
	{
//		go_redir(*(*line)->stream);		// 리다이렉션 배열에서 맞는 fd로 dup2
//		go_redir(*stream, fd1);		// 테스트용
		split_arg((&temp), temp->arg);
		temp = temp->next;
		stream++;			// 테스트용
//		((*line)->stream)++;
	}
//	dup2(fd_temp, 1);
//	back_redir(*(*line)->stream);		// 다시 fd 0,1 맞춰줌
}

void	send_pipe(t_line *last)		// 재귀 호출로 분기하고 다음으로 보냄
{
	pid_t	pid;
	int		*status;
	int		state;

int		fd1;		// 파이프 때문에 일단 선언해 놓은 변수들
int		fd_temp;
int		*pipe2;
int		temp_stdin;
int		temp_stdout;

	pid = 0;
	pipe2 = (int *)malloc(sizeof(int) * 2);
	state = pipe(pipe2);

	if (last->prev)
	{
		pid = fork();					// dup2를 하고 close함수를 활용하자
		printf("generate %d\n", pid);
		if (pid != 0)
			wait(status);
		else
		{
			send_pipe(last->prev);
			split_arg((&last), last->arg);
			exit(0);
		}
	}
	else
		split_arg((&last), last->arg);
}

void split_pipe(t_line **line, char *pipe_line) // echo >aa >bb c | pwd
{
	t_line *pipe_list;
	t_line *temp;
	pid_t	pid;

	pipe_list = NULL;
	(*line)->line = pipe_list; 
	temp = pipe_list;
	send_pipe(ft_listlast(temp));		// pipe함수 사용
}

void  split_semi(t_line **line) // echo >a >b >c | pwd ; ls
{
	t_line *semi_list;
	t_line *temp;
	int	i;

	i = 0;
	semi_list = NULL;
	(*line)->line = semi_list;
	temp = semi_list;
	while(temp != NULL)
	{
		split_pipe((&temp), temp->arg);
		temp = temp->next;
		i++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char	*input_line;
//	char *input = "echo hi | everyone ; pwd | grep ; ls";
	t_line	*line;
	t_line	*down;
	int	lvl;

	if (argc != 1 || argv[1])
	{
		write(1, "cannot excute binary file\n", 26);
		return (0);
	}
	init_env(envp);
	write(1, "KJMSHell(OoO) >> ", 17);		 // 3번째 인자 22로 하면 터집니다..
	while ((parse_line(&input_line)) > 0)
	{
		if (input_line[0] == '$' && input_line[1] == '?')
		{
			printf("ft_errno %d\n", ft_errno);
		}
//		lvl = 1;
		line = ft_listnew(input_line);
//		split_semi(&line);
		make_list(&line, input_line);
//		down = line;
		write(1, "KJMSHell(OoO) >> ", 17);
		free(line);
	}
	return (0);
}
