#include "minishell.h"

t_line		*ft_listnew(char *content)
{
	t_line	*lst;

	if (!(lst = (t_line *)malloc(sizeof(t_line) * 1)))
		return (NULL);
	lst->arg = content;
	lst->next = NULL;
	lst->prev = NULL;		// prev 추가
	return (lst);
}
