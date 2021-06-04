/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_util2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:27:58 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 12:58:15 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		split_malloc(char ***split, int word_num2)
{
	(*split) = (char **)malloc(sizeof(char *) * (word_num2 + 1));
	(*split)[word_num2] = NULL;
}

int			next_when_is_space(char **s)
{
	int		i;

	i = 0;
	while (is_space(*(*s)))
	{
		(*s)++;
		i++;
	}
	return (i);
}

int			is_space(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void		free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int			is_quote(const char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
