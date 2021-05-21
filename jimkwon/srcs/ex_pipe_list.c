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
		printf("%s -> ", temp->arg);
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
		printf("%s  ->   ", (*temp)->arg);
		*temp = (*temp)->next;
		i--;
	}
}

int main()
{
	t_line *list;
	t_line *temp;
	t_line *iter;
	t_line **ptr_list;
	int i;
	int index = 0;

	list = NULL;
	//pwd -> | ls -> | -> pwd -> ; -> echo -> abc
	ft_listadd_back(&list, ft_listnew("pwd"));
	ft_listadd_back(&list, ft_listnew("ls"));
	ft_listadd_back(&list, ft_listnew("|"));
	ft_listadd_back(&list, ft_listnew("ls"));
	ft_listadd_back(&list, ft_listnew("a"));
	ft_listadd_back(&list, ft_listnew("|"));
	ft_listadd_back(&list, ft_listnew("pwd"));
	ft_listadd_back(&list, ft_listnew("|"));
	ft_listadd_back(&list, ft_listnew("echo"));
	ft_listadd_back(&list, ft_listnew("abc"));
	temp = list;
	iter = list;
	ptr_list = (t_line **)malloc(sizeof(t_line *) * (3 + 2)); //나중엔 pip + 2로
	while (temp != NULL)
	{
		i = ft_split_list_token(temp, '|');
		temp = ft_list_null_term(temp, i);
		ptr_list[index] = iter;
		ft_listiter(ptr_list[index]);
		//printf("%s\n", (*(ptr_list[index]))->arg);
		index++;
		iter = temp;
		printf("\n");
	}
}