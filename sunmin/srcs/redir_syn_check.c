#include "minishell.h"

int		redir_syn_check(t_line **line)
{
	t_line **lst;

	lst = line;
	while (*lst)
	{
		printf("cc %c\n", (*lst)->arg[0]);
		if ((*lst)->arg[0] == '>' || (*lst)->arg[0] == '<')
		{
			if ((*lst)->arg[0] == '>')
			{
				*lst = (*lst)->next;
				if ((*lst)->arg[0] == '<' || !(*lst))
				{
					printf("redir syn error\n");
					return (-1);
				}
				else if ((*lst)->arg[0] == '>')
				{
					*lst = (*lst)->next;
					if ((*lst)->arg[0] == '<' || !(*lst))
					{
						printf("redir syn error\n");
						return (-1);
					}
				}
			}
			else		// <
			{
				*lst = (*lst)->next;
				if ((*lst)->arg[0] == '>' || !(*lst))
				{
					printf("redir syn error\n");
					return (-1);
				}
				else if ((*lst)->arg[0] == '<')
				{
					*lst = (*lst)->next;
					if ((*lst)->arg[0] == '>' || !(*lst))
					{
						printf("redir syn error\n");
						return (-1);
					}
				}
			}
		}
		else
			*lst = (*lst)->next;
	}
	return (0);
}
