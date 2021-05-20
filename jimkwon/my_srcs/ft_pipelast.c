#include "minishell.h"

t_pipe		*ft_pipelast(t_pipe *lst)
{
	t_pipe	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
