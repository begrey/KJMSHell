/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syn_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:00:37 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 09:03:48 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			syntax_print()
{
	printf("a\n");
	printf("syntax error near unexpected token\n");
	printf("b\n");
	return (-1);
}

static int	semi_pipe(char *s)
{
	if (ft_strcmp(s, ";") == 0 || ft_strcmp(s, "|") == 0)
		return (1);
	return (0);
}

int			token_syn_check(t_line *line, char **split)
{
	t_line *temp;

	temp = line;
	if (line && semi_pipe((line)->arg))
	{
		free_struct(line);
		free_split(split);
		return (syntax_print());
	}
	while (temp)
	{
		if (is_token(temp->arg))
		{
			if (temp->next == NULL && temp->arg[0] != ';')
			{
				free_struct(line);
				free_split(split);
				return (syntax_print());
			}
			if (temp->next)
				temp = temp->next;
			else
				return (0);
			if (temp && is_token(temp->arg))
			{
				free_struct(line);
				free_split(split);
				return (syntax_print());
			}
		}
		temp = temp->next;
	}
	return (0);
}
