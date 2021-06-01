#include "minishell.h"

void	free_struct(t_line *list)
{
	if (list)
	{
		free(list->arg);
		free(list);
	}
}
