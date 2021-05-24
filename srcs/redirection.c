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
				temp = temp->next;
				if (is_redir(temp->arg[0]))
				{
					type = 2;
					temp = temp->next;
				}
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

void	ft_list_delredir(t_line *line)		// >a만 올 때 세그폴트
{
	t_line	*temp;

	temp = line;
	if (which_redir((temp)->arg))
	{
		(temp) = (temp)->next;
		(temp)->prev = NULL;
	}
	temp = line;

	while (temp)
	{
		if (which_redir(temp->arg))
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp = temp->next;
			temp->prev->next = temp->next;
			if (temp->next)
					temp->next->prev = temp->prev;
		}
		temp = temp->next;
	}

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


int		ft_redirection(t_line *line)
{
	int		re_num;
	int		i;
	char	**re_name;
	int		*re_type;
	t_line	*temp;
	int		status;
	pid_t	pid;
	int		fd_wr;
	int		fd_op;
	int		j;

	temp = line;

	re_num = redir_num(temp);
	re_name = (char **)malloc(sizeof(char *) * (re_num + 1));
	re_type = (int *)malloc(sizeof(int) * (re_num));
	temp = line;
	put_redir(temp, &re_name, &re_type);

	// 리다이렉션 구조체 삭제(ing)		// >a 만 입력하면 세그폴트 (sunmin/maina문 문제일수도)
	temp = line;
	ft_list_delredir(temp);

	// escape 제거
	temp = line;
	while (temp)
	{
		temp->arg = delete_escape(temp->arg);
		temp = temp->next;
	}
	
	// 리스트에서 quote 제거(ing)
	temp = line;
	while (temp)
	{
		temp->arg = ft_del_quote(temp->arg);
		temp = temp->next;
	}

	// 아스키 -값 복원
	temp = line;
	while (temp)
	{
		temp->arg = restore_escape(temp->arg);
		temp = temp->next;
	}









	fd_wr = 0;
	fd_op = 0;
	i = 0;
	while (i < re_num)
	{
		if (re_type[i] == 1)		// >
		{
			fd_wr = open(re_name[i], O_RDWR | O_CREAT | O_TRUNC, 00777);
		}
		else if (re_type[i] == 2)	// >>
		{
			fd_wr = open(re_name[i], O_RDWR | O_CREAT | O_APPEND, 00777);
		}
		else if (re_type[i] == 3)	//	<
		{
			if ((fd_op = open(re_name[i], O_RDONLY, 00777)) < 0)
			{
				printf("no file read\n");
				return(-1);
			}
			else
				;
		}
		i++;
	}

		temp = line;//
/*	
	pid = fork();
	printf("1 %d\n", pid);
	if (pid != 0)
		wait(&status);
	else
	{
*/
		temp = line;
		if (re_num)
		{
			if (fd_wr)
				dup2(fd_wr, 1);
			if (fd_op)
			{
				i = 0;
				while (re_name[i])
				{
					if (re_type[i] == 3)
						j = i;
					i++;
				}
				exec_command(temp, re_name[j]);
			}
		}
		else
//		{
			exec_command(temp, NULL);
			//close(fd_wr);
			//exit(0);
//		}
//	}
	return (0);
	status = 0;
	j = 0;
	pid = 0;
}
