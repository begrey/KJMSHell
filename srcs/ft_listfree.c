#include "minishell.h"

void	free_struct(t_line *list)
{
	t_line *temp;

	temp = list;
	while (temp)
	{
		list = list->next;
		free(temp);
		temp = list;
	}
}
