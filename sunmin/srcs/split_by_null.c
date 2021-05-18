#include "minishell.h"

int ft_listiter(t_line *lst)
{
	int i;
	t_line *temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		i++;
		printf("%s -> \n", temp->arg);
		temp = temp->next;
	}
	return (i);
}

t_line *ft_list_null_term(t_line *lst, int index)
{
	int i;
	t_line *temp;

	i = 0;
	while (lst != NULL)
	{
		if (i == (index - 1))
		{
			if (lst->next == NULL) //token 없이 마지막 null만날때,
				temp = lst->next;
			else
				temp = lst->next->next;
			lst->next = NULL;
			return (temp);	
		}
		lst = lst->next;
		i++;
	}
	return lst;
}

int ft_split_list_token(t_line *lst, char token)
{
	int i;
	t_line *temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		if (temp->arg[0] == token)
			return (i);
		i++;
		temp = temp->next;
	}
	return (i);
}


void ft_move_temp(t_line **temp, int i)
{
	while (temp != NULL && i != 0)
	{
		printf("%s  ->  \n", (*temp)->arg);
		*temp = (*temp)->next;
		i--;
	}
}

void	split_by_pipe(t_line **line)
{
	t_line *temp;
	t_line *iter;
	int		i;

	temp = *line;
	iter = *line;
	while (temp != NULL)
	{
		i = ft_split_list_token(temp, '|');
		printf("pipe arg : %s  i : %d\n", temp->arg, i);
		temp = ft_list_null_term(temp, i);
		ft_listiter(iter);
//		pipe_split(iter)		나중에 구현할 함수
		iter = temp;
		printf("\n");
	}
}

void	split_by_semi(t_line **line)
{
	t_line *temp;
	t_line *iter;
	int		i;

	temp = *line;
	iter = *line;
	while (temp != NULL)
	{
		i = ft_split_list_token(temp, ';');
		printf("semi arg : %s  i : %d\n", temp->arg, i);
		temp = ft_list_null_term(temp, i);
		ft_listiter(iter);
		split_by_pipe(&iter);
		iter = temp;
		printf("\n");
	}
}


/*
int main()
{
	t_line *list;
	t_line *temp;
	t_line *iter;
	int i;

	list = NULL;
	//pwd -> | ls -> | -> pwd -> ; -> echo -> abc
	ft_listadd_back(&list, ft_listnew("pwd"));
	ft_listadd_back(&list, ft_listnew("ls"));
	ft_listadd_back(&list, ft_listnew("|"));
	ft_listadd_back(&list, ft_listnew("ls"));
	ft_listadd_back(&list, ft_listnew("|"));
	ft_listadd_back(&list, ft_listnew("pwd"));
	ft_listadd_back(&list, ft_listnew("pwd"));
	ft_listadd_back(&list, ft_listnew(";"));
	ft_listadd_back(&list, ft_listnew("echo"));
	ft_listadd_back(&list, ft_listnew("abc"));
	temp = list;
	iter = list;
	while (temp != NULL)
	{
		i = ft_split_list_token(temp, ';');
		//printf("arg : %s  i : %d\n", temp->arg, i);
		temp = ft_list_null_term(temp, i);
		ft_listiter(iter);
		iter = temp;
		printf("\n");
	}
}
*/
