#include "minishell.h"

void	free_struct(t_line *list)
{
	t_line *temp;

	temp = list;
	while (temp)
	{
		list = list->next;
		free(temp->arg);
		free(temp);
		temp = list;
	}
}

void	free_pipe(t_pipe *list)
{
	t_pipe *temp;

	temp = list;
	while (temp)
	{
		list = list->next;
		free(temp);
		temp = list;
	}
}

void	free_list_struct(t_line **list)
{
	int i;
	t_line *temp;

	i = 0;
	while (list[i] != NULL)
	{
		temp = list[i];
		while (temp)
		{
			list[i] = (list[i])->next;
			free(temp->arg);
			free(temp);
			temp = list[i];
		}
		i++;
	}
	free(list);
}