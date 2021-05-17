#include "minishell.h"

/*
void	parse_redirection(t_line **list)
{
	while (*list)
	{
		if ((*list)->arg[0] == '>' || (*list)->arg[0] == '<')
		{
			if ((*list)->arg[0] == '>')
			{
				*list = (*list)->next;
			}
			else
			{

			}
		}
		else
		{
;
		}
		*list = (*list)->next;
	}
}
*/

int		is_token(char c)
{
	if (c == ';' || c == '|' || c == '>' || c == '<')		// <, >는 따로 처리해야 할 듯
		return (1);
	return (0);
}



int		is_token_quote(const char *str)
{
	char		*s;
	char		flag;
	int			ret;

	ret = 0;
	flag = 0;
	s = (char *)str;


	while (*s && *(s + 1))
	{
		if (is_token(*(s + 1)))
			ret++;
		flag = flag_check(*s, flag);	// 함수이름 바꿔야함
		if (!flag)			// quote 가 없을 때는 토큰 취급
		{
			if (is_token(*s))
				ret++;
		}
		s++;
	}
	if (*s)
		ret++;
	return (ret);
}

int		where_token(char *str)	// is_token_quote와 구조 비슷	// 토큰의 인덱스 반환
{
	char		*s;
	char		flag;
	int			ret;
	int			i;

	i = 0;
	s = (char *)str;
	ret = 0;
	flag = 0;
	while (s[i])
	{
		flag = flag_check(s[i], flag);
		if (!flag)
		{
			if (is_token(s[i]))
				return (i);
		}
		i++;
	}
	return (i);
}

char	**ft_token_split(char *arg)
{
	char	*s;
	char	**split_token;
	int		next_split;
	int		split_num;
	int		word_num;
	int		i;
	int		j;

	s = (char *)arg;
	split_num = is_token_quote(arg);
	split_token = (char **)malloc(sizeof(char *) * (split_num + 1));
	split_token[split_num] = NULL;
	i = 0;
	next_split = where_token(s);	////// 수정 필요 // 개수 받아오는 것과 다음 포인터 반환하는 것이 잘 안됨
	while (i < split_num)
	{
		if (is_token(*s))
		{
			split_token[i] = (char *)malloc(sizeof(char) * (2));
			split_token[i][0] = *s;
			split_token[i][1] = '\0';
			s++;
		}
		else
		{
			j = 0;
			word_num = where_token(s);// - next_split;	//// 수정 필요
		split_token[i] = (char *)malloc(sizeof(char) * (word_num + 1));
			split_token[i][word_num] = '\0';
			while (j < word_num)
			{
				split_token[i][j] = *s;
				j++;
				s++;
			}
		}
		next_split = where_token(s + next_split + 1);	//// 수정 필요
		i++;
	}
	return (split_token);
}

void	list_split_addback(t_line **lst, char *arg)		//arg로는 >a;|as";|>"er 같은 값이 들어옴
{

	int		i;
	char	**split_token;		// 토큰 기준으로 스플릿

	i = 0;
	// 토큰 기준으로 스플릿하기만하면 됨
	split_token = ft_token_split(arg);
	// 나눠놓은 문자열 붙이기
	while (split_token[i])
	{
		ft_listadd_back(lst, ft_listnew(split_token[i]));
		i++;
	}

}

void	make_list(t_line **line, char *s_line)
{
	char **split_line;
	int i;

	split_line = ft_split_quote(s_line);
	i = 0;
	while (split_line[i])				// 환경변수 변환
	{
		split_line[i] = convert_env(split_line[i]);
		printf("line[%d] :%s\n", i, split_line[i]);
		i++;
	}
	printf("-----------\n");
	i = 0;
	while (split_line[i])
	{
		if (is_token_quote(split_line[i]))
			list_split_addback(line, split_line[i]);
		else
			ft_listadd_back(line, ft_listnew(split_line[i]));
		i++;
	}
	printf("list test \n\n");
	while (*line)		// 출력 테스트
	{
		printf("%s\n", (*line)->arg);
		*line = (*line)->next;
	}

/*
	while (*line)			// 토큰 분할하는 함수
	{
		
		*line = (*line)->next;
	}
*/

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
	write(1, "KJMSHell(OoO) >> ", 17);
	while ((parse_line(&input_line)) > 0)
	{
		if (input_line[0] == '$' && input_line[1] == '?')
		{
			printf("ft_errno %d\n", ft_errno);
		}
//		lvl = 1;
//		line = ft_listnew(input_line);
//		split_semi(&line);
		make_list(&line, input_line);
//		down = line;
		write(1, "KJMSHell(OoO) >> ", 17);
		free(line);
	}
	return (0);
}
