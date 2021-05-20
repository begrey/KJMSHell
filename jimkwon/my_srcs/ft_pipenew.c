#include "minishell.h"

t_pipe		*ft_pipenew(int *pipe)
{
	t_pipe	*lst;

	if (!(lst = (t_pipe *)malloc(sizeof(t_pipe) * 1)))
		return (NULL);
	//lst->fd = pipe;
	lst->next = NULL;
	return (lst);
}
