/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syn_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:59:26 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 14:13:07 by sunmin           ###   ########.fr       */
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

int			redir_syn_check(t_line *line)
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
				printf("syntax error near unexpected token\n");
				return (-1);
			}
		}
		lst = lst->next;
	}
	return (0);
}