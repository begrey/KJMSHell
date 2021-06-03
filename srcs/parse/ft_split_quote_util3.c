/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_util3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:28:29 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 15:33:35 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		if_not_flag_quote(char **s, int *word_num)
{
	if (is_space(*(*s)))
	{
		while (is_space(*(*s)))
			(*s)++;
		if (*(*s))
		{
			(*word_num)++;
			(*s)--;
		}
	}
}

void		is_space_len(char **s, int *word_num, int **word_len2, int *len)
{
	while (is_space(*(*s)))
		(*s)++;
	if (*(*s))
	{
		(*word_num)++;
		*(*word_len2) = *len;
		(*word_len2)++;
		(*len) = 0;
		(*s)--;
	}
}
