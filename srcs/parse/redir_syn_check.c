/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syn_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:59:26 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 13:55:43 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			which_redir(char *s)
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
	if (c == '#' || c == '&' || c == ')')
		return (1);
	return (0);
}

void		free_syntax_error(t_line *line, char **split)
{
	free_struct(line);
	free_split(split);
}

void		init_redir_syn(int *n, t_line **lst, t_line *line)
{
	(*n) = 0;
	(*lst) = line;
}

int			redir_syn_check(t_line *line, char **split)
{
	t_line	*lst;
	int		n;

	init_redir_syn(&n, &lst, line);
	while (lst)
	{
		if (which_redir(lst->arg) && (!lst->next || !(lst->next->arg[0])))
		{
			free_syntax_error(line, split);
			printf("syntax error near unexpected token \'newline\'\n");
			return (-1);
		}
		if ((n = which_redir(lst->arg)) != 0)
		{
			lst = lst->next;
			if (which_redir(lst->arg) || forbidden_char(lst->arg[0]))
			{
				free_syntax_error(line, split);
				printf("syntax error near unexpected token\n");
				return (-1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
