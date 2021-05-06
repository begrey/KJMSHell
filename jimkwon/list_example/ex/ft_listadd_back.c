#include "minishell.h"

void		ft_listadd_back(t_line **lst, t_line *new)
{
	t_line	*last;
	t_line	*temp;

	temp = *lst;
	if (temp == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	temp = *lst;
	last = ft_listlast(temp);
	last->next = new;
}
