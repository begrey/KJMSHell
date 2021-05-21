#include "minishell.h"


int	which_redir(char *s)
{
	if (ft_strcmp(s, ">") == 0)
		return (1);
	else if (ft_strcmp(s, ">>") == 0)
		return (2);
	if (ft_strcmp(s, "<") == 0)
		return (3);
	return (0);
}

static int	forbidden_char(char c)
{
	if (c == '#' || c == '&' || c == ')')		// 배쉬와 zsh이 다름
		return (1);
	return (0);
}

int		redir_syn_check(t_line *line)
{
	t_line	*lst;
	int		n;

	n = 0;
	lst = line;
	while (lst)
	{
		if (which_redir(lst->arg) && !lst->next)
		{
			printf("syntax error near unexpected token \'newline\'\n");
			return (-1);
		}
		if ((n = which_redir(lst->arg)) != 0)
		{
			lst = lst->next;
			if (which_redir(lst->arg) || forbidden_char(lst->arg[0]))
			{
				printf("syntax error near unexpected token \'%c\'\n", lst->arg[0]);
				return (-1);
			}
		}
		lst = lst->next;
	}
	return (0);
}

/*
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
*/
