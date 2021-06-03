/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syn_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:00:37 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 14:20:11 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			syntax_print(char c)
{
	printf("syntax error near unexpected token \'%c\'\n", c);
	return (-1);
}

static int	semi_pipe(char *s)
{
	if (ft_strcmp(s, ";") == 0 || ft_strcmp(s, "|") == 0)
		return (1);
	return (0);
}

int			token_syn_check(t_line *line)
{
	t_line *temp;

	temp = line;
	if (line && semi_pipe((line)->arg))
		return (syntax_print(line->arg[0]));
	while (temp)
	{
		if (is_token(temp->arg))
		{
			if (temp->next == NULL && temp->arg[0] != ';')
				return (syntax_print(line->arg[0]));
			temp = temp->next;
			if (temp && is_token(temp->arg))
				return (syntax_print(line->arg[0]));
		}
		temp = temp->next;
	}
	return (0);
}
