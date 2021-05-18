#include "minishell.h"

int		is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int		put_redir(t_line **line, char ***re_name, int **re_type, int num)
{
	printf("put_redir start\n");
	t_line	**temp;
	int		flag;
	int		type;
	int		i;

	temp = line;
	while (*temp)
	{
		type = 0;
		if (is_redir((*temp)->arg[0]))
		{
			type = 1;
			*temp = (*temp)->next;
			if (is_redir((*temp)->arg[0]))
			{
				type = 2;
				*temp = (*temp)->next;
			}

			flag = 0;
			printf("bbbarg %s\n", (*temp)->arg);
			while (*temp && !is_redir((*temp)->arg[0]))
			{
				if (flag == 0)
				{
					printf("aaaaaaaaaaarg %s\n", (*temp)->arg);
					(*re_type)[i] = type;
					(*re_name)[i] = ft_strdup((*temp)->arg);
				}
				*temp = (*temp)->next;
				flag++;
			}
			i++;
		}
		if (*temp && !is_redir((*temp)->arg[0]))
			*temp = (*temp)->next;
	}
	int k = 0;
	while (k < num)
	{
		printf("num = %d, type = %d, name = %s\n", k, (*re_type)[k], (*re_name)[k]);
		k++;
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

int		ft_redirection(t_line **line)		// 앞에서 syntax 체크 다 했기 때문에 정상적인 값만 들어온다고 가정
{

	int		re_num;
	int		i;
	char	**re_name;
	int		*re_type;
	t_line	**temp;

	while (*line)
	{
		printf("ee %s\n", (*line)->arg);
		*line = (*line)->next;
	}
	temp = line;
	re_num = redir_num(temp);		//  개수 체크	// 포인터가 넘어감		// ㅠㅠ
	printf("rr %d\n", re_num);
	while (*line)
	{
		printf("ss %s\n", (*line)->arg);
		*line = (*line)->next;
	}
	re_name = (char **)malloc(sizeof(char *) * (re_num + 1));
	re_type = (int *)malloc(sizeof(int) * (re_num));
	put_redir(line, &re_name, &re_type, re_num);
	return (0);
}
