#include "./minishell.h"

int		ft_listsize(t_line *line)
{
	t_line	*temp;
	int		len;

	len = 0;
	temp = line;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
