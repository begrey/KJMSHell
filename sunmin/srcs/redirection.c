#include "minishell.h"

int		is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int		put_redir(t_line **line, char ***re_name, int **re_type, int num)
{
	t_line	*temp;
	int		flag;
	int		type;
	int		i;

	temp = *line;
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

int		redir_num(t_line **line)		// 구조체 안에 redir 정보 넣는 것 까지 같이
{
	int		num;
	t_line	**temp;

	num = 0;
	temp = line;
	while (*temp)
	{
		if (is_redir((*temp)->arg[0]))
		{
			*temp = (*temp)->next;
			if (is_redir((*temp)->arg[0]))
				*temp = (*temp)->next;
			while (*temp && !is_redir((*temp)->arg[0]))
				*temp = (*temp)->next;
			num++;
		}
		if (*temp && !is_redir((*temp)->arg[0]))
			*temp = (*temp)->next;
	}
	return (num);
}

void	ft_list_delredir(t_line **line)
{
	t_line	*temp;
	if (is_redir((*line)->arg[0]))
	{
		(*line) = (*line)->next;
		(*line)->prev = NULL;
	}
	temp = *line;
	while (temp)
	{
		if (is_redir(temp->arg[0]))
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp = temp->next;
			if (is_redir(temp->arg[0]))
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp = temp->next;
			}
			temp->prev->next = temp->next;
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


int		ft_redirection(t_line **line)		// 앞에서 syntax 체크 다 했기 때문에 정상적인 값만 들어온다고 가정
{

	// 리다이렉션 >   > 일때 >, > 를 2개의 리스트로 만드는 것이 아니라 >> 하나의 리스트로 만들어야 함
	int		re_num;
	int		i;
	char	**re_name;
	int		*re_type;
	t_line	*temp;




	temp = *line;
//	while (*line)		// 출력
//	{
//		printf("ee %s\n", (*line)->arg);
//		*line = (*line)->next;
//	}
	re_num = redir_num(&temp);		//  개수 체크
	re_name = (char **)malloc(sizeof(char *) * (re_num + 1));
	re_type = (int *)malloc(sizeof(int) * (re_num));
	put_redir(line, &re_name, &re_type, re_num);




	// 리다이렉션 구조체 삭제(ing)
	ft_list_delredir(line);		// echo >a ">b" "cc" d 하면 중간에 빈 리스트 생김



	// 리스트에서 quote 제거(ing)
	while (temp)
	{
		(temp)->arg = ft_del_quote((temp)->arg);
		temp = (temp)->next;
	}



	// 리다이렉션 만들기	// dup2 사용
	// 리다이렉션을 먼저 실행해서 <> 모두 확인
	

/*
	i = 0;
	while (i < re_num)
	{
		if (re_type[i] == 1)		// >
		{
			open(re_name[i], O_RDWR | O_CREAT | O_TRUNC, 00777);
		}
		else if (re_type[i] == 2)	// >>
		{
			open(re_name[i], O_RDWR | O_CREAT | O_APPEND, 00777);
		}
		else if (re_type[i] == 3)	//	<
		{
			if (!(open(re_name[i], O_RDONLY, 00777)))
			{
				printf("4\n");
				printf("no file read\n");
				break;		// break가 아니라 포크해서 해야하나
			}
			else
		}
		i++;
	}
*/

/*
	int j;
	i = 0;
	while (re_name[i])
	{
		if (re_type[i] == 1 || re_type[i] == 2)
			j = i;
		i++;
	}
//	dup2(0, re_name[j]);
	i = 0;
	while (re_name[i])
	{
		if (re_type[i] == 1 || re_type[i] == 2)
			j = i;
		i++;
	}

*/

	// 포크 해야함
//	dup2(1, re_name[j]);		// 마지막 리다이렉션만 write로 사용
	// open 을 다시 해서 fd를 받아와야 함
	//exec(line);		// 실행부로 넘김

//	while (*line)
//	{
//		printf("dd %s\n", (*line)->arg);
//		*line = (*line)->next;
//	}

//	ft_exec(line);
	return (0);
}
/*
int		main(void)
{
	char *str;
	int	num;
	char	*after;

	str = ft_strdup("ab\'d \'\'f\'d\'\"\'\"dd\"");// abd "(5) 	// ab'd ''f'd'"'"dd" -> abd fd"dd 나와야 함
	num = check_num_delquote(str);
	printf ("%s\n", str);
	printf("qoute del num %d\n", num);
	after = ft_del_quote(str);
	printf("after %s\n", after);
	return (0);
}
*/