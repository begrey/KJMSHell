#include "minishell.h"

void		ft_pipeadd_back(t_pipe **pip, t_pipe *new)
{
	t_pipe	*last;
	t_pipe	*temp;

	temp = *pip;
	if (temp == NULL)
	{
		*pip = new;
		new->next = NULL;
		return ;
	}
	temp = *pip;
	last = ft_pipelast(temp);
	last->next = new;
}
