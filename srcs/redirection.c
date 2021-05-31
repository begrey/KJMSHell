#include "minishell.h"

int		is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int		put_redir(t_line *line, char ***re_name, int **re_type)
{
	t_line	*temp;
	int		flag;
	int		type;
	int		i;

	i = 0;
	temp = line;
	while (temp)			// 1,2,3 으로 다시 해야 함		 >=1, >>=2, <=3
	{
		type = 0;
		if (is_redir(temp->arg[0]))
		{
			if (temp->arg[0] == '<')
			{
				type = 3;
				temp = temp->next;
			}
			else
			{	
				type = 1;
				if (temp->arg[1] == '>')
					type = 2;
				temp = temp->next;
			}
			flag = 0;
			while (temp && !is_redir(temp->arg[0]))
			{
				if (flag == 0)
				{
					(*re_type)[i] = type;
					(*re_name)[i] = ft_strdup(temp->arg);
				}
				temp = temp->next;
				flag++;
			}
			i++;
		}
		if (temp && !is_redir(temp->arg[0]))
			temp = temp->next;
	}
	return (0);
}

int		redir_num(t_line *line)		// 구조체 안에 redir 정보 넣는 것 까지 같이
{
	int		num;
	t_line	*temp;

	num = 0;
	temp = line;
	while (temp)
	{
		if (is_redir(temp->arg[0]))
		{
			temp = temp->next;
			if (is_redir(temp->arg[0]))
				temp = temp->next;
			while (temp && !is_redir(temp->arg[0]))
				temp = temp->next;
			num++;
		}
		if (temp && !is_redir(temp->arg[0]))
			temp = temp->next;
	}
	return (num);
}

t_line	*ft_list_delredir(t_line *line)		// 세니타이저 에러 있음
{
	t_line	*temp;
	t_line	*free1;
	t_line	*free2;

	if (!line)
	{
		line = ft_listnew(ft_strdup(""));
		return (line);
	}
	while (line && which_redir((line)->arg))
	{
		free1 = line;
		free2 = line->next;
		(line) = (line)->next->next;
		if (free1)
			free(free1);
		if (free2)
			free(free2);
		if (line != NULL)
			(line)->prev = NULL;
	}
	temp = line;
	while (temp)
	{
		if (which_redir(temp->arg))
		{
			free1 = temp;
//			free2 = temp->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
//			free(free1);
			temp = temp->next;
			free1 = temp;
//			temp->prev->next = temp->next;
//			free(free2);
			if (temp->next && temp->prev)
			{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
			}
		}
		temp = temp->next;
	}
	return (line);
}

int		check_num_delquote(char *str)		// 잘됨
{
	int		num;
	char	*s;
	int		flag;
	int		compare;

	flag = 0;
	num = 0;
	s = (char *)str;
	while (*s)
	{
		compare = flag;
		flag = flag_check(*s, flag);
		num++;
		if (flag != compare)
			num--;
		s++;
	}
	return (num);
}



char	*ft_del_quote(char *str)
{
	char	*temp;
	char	flag;
	char	*s;
	int		i;
	int		j;
	int		num;
	char	compare;
	int		*quote;

	num = check_num_delquote(str);
	temp = (char *)malloc(sizeof(char) * (num + 1));
	temp[num] = '\0';
	quote = (int *)malloc(sizeof(int) * (ft_strlen(str) - num));
	s = (char *)str;
	flag = 0;

	i = 0;
	j = 0;
	while (*s)
	{
		compare = flag;
		flag = flag_check(*s, flag);
		if (compare != flag)
			s++;
		else
		{
			temp[i] = *s;
			i++;
			s++;
		}
	}
	return (temp);
}


int		ft_redirection(t_line *line, t_env *env, int pip_flag)
{

	int		re_num;
	int		i;
	char	**re_name;
	int		*re_type;
	t_line	*temp;
	int		status;
	int		fd_wr;
	int		fd_op;
	int		j;
	char	*temp_str;

	temp = line;
	re_num = redir_num(temp);
	re_name = (char **)malloc(sizeof(char *) * (re_num + 1));
	re_type = (int *)malloc(sizeof(int) * (re_num));
	temp = line;
	put_redir(temp, &re_name, &re_type);






	// 리다이렉션 구조체 삭제(ing)			// 릭 잡는 중
	temp = line;
	line = ft_list_delredir(temp);		// 세니타이저 에러 || 누수(free)







	//	escape 제거
	temp = line;							// 릭 제거
	while (temp)
	{
		temp_str = temp->arg;
		temp->arg = delete_escape(temp->arg);
//		free(temp_str); 있으면 세니타이즈 에러
		temp = temp->next;
	}







	// 리스트에서 quote 제거(ing)			// 릭 제거
	temp = line;
	while (temp)
	{
		temp_str = temp->arg;
		(temp)->arg = ft_del_quote((temp)->arg);
		free(temp_str);
		temp = (temp)->next;
	}






	// 아스키 -값 복구						// 릭 제거
	temp = line;
	while (temp)
	{
		temp_str = temp->arg;
		temp->arg = restore_escape(temp->arg);
		free(temp_str);
		temp = temp->next;
	}



	fd_wr = -1;
	j = -1;
	i = 0;
	while (i < re_num)
	{
		if (re_type[i] == 1)		// >
		{
			fd_wr = open(re_name[i], O_RDWR | O_CREAT | O_TRUNC, 00777);
		}
		else if (re_type[i] == 2)	// >>
		{
			fd_wr = open(re_name[i], O_RDWR | O_APPEND | O_CREAT, 00777);
		}
		else if (re_type[i] == 3)	//	<
		{
			j = i;
			// printf("?\n");
			if ((fd_op = open(re_name[i], O_RDONLY, 00777)) < 0)
			{
				printf("????? %s\n", strerror(errno));
				put_return(1, env);
				return(0);
			}
		}
		i++;
	}


	temp = line;
	if (j == -1 || temp->next != NULL)
	{
		j = 0;					// 나중에 다시 생각해봐야
		re_name[j] = NULL;
	}
	status = 0;
	temp = line;
	if (fd_wr > 0)
		dup2(fd_wr, 1);
	exec_command(temp, re_name[j], env, pip_flag);
	if (!(close(fd_wr)))
		printf("not\n");
	return (status); // exec에서 종료하기때문에 이 구문이 실행되지 않는다.
}
