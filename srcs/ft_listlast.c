#include "minishell.h"

t_line		*ft_listlast(t_line *lst)
{
	t_line	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
