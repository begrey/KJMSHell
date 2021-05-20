#include "minishell.h"

int		redir_syn_check(t_line **line)		// 입력 제대로 들어옴
{
	t_line *lst;

	lst = *line;
	while (lst)
	{
		if ((lst)->arg[0] == '>' || (lst)->arg[0] == '<')
		{
			if ((lst)->arg[0] == '>')
			{
				lst = (lst)->next;
				if (lst && (lst)->arg[0] == '<')
				{
					if (!(lst))
						printf("syntax error near unexpected token \'newline\'\n");
					else	
						printf("syntax error near unexpected token \'%s\'\n", (lst)->arg);
					return (-1);
				}
				else if (lst && (lst)->arg[0] == '>')
					redir_syn_check(&lst);
				else if  (!lst)
				{
					printf("syntax error near unexpected token \'newline\'\n");
					return (-1);
				}
			}
			else	// <
			{
				lst = (lst)->next;
				if (lst)
				{
					if ((lst)->arg[0] == '>' || (lst)->arg[0] == '<')
					{
						printf("syntax error near unexpected token \'%s\'\n", (lst)->arg);
						return (-1);
					}
				}
				else if (!lst)
				{
					printf("syntax error near unexpected token \'newline\'\n");
					return (-1);
				}
			}
		}
		else
			lst = (lst)->next;
	}
	return (0);
}
