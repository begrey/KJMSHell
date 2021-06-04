/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:27:30 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 10:04:29 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		split_i_malloc(char **split, int *word_len, int i)
{
	split[i] = (char *)malloc(sizeof(char) * (word_len[i] + 1));
	split[i][word_len[i]] = '\0';
}

void		check_space_word_num(char **s, int *word_num, int *len)
{
	while (is_space(*(*s)))
		(*s)++;
	if (*(*s))
	{
		(*word_num)++;
		(*len) = 0;
		(*s)--;
	}
}

int			check_word_num_return(char *s, int *word_num)
{
	if (*s)
		*word_num = 1;
	else
	{
		*word_num = 0;
		return (0);
	}
	return (1);
}

char		**return_if_null(char **split)
{
	split = (char **)malloc(sizeof(char *) * (2));
	split[1] = NULL;
	split[0] = ft_strdup("");
	return (split);
}

char		**return_if_flag(int *word_len, char **split, char *s)
{
	free(s);
	free(word_len);
	free_split(split);
	return (NULL);
}
