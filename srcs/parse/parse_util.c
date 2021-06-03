/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:28:51 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 20:59:06 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_bytes(char **split_token, char *s, int i)
{
	int		j;
	int		word_num;

	j = -1;
	word_num = where_token(s);
	split_token[i] = (char *)malloc(sizeof(char) * (word_num + 1));
	split_token[i][word_num] = '\0';
	while (++j < word_num)
	{
		split_token[i][j] = *s;
		s++;
	}
	return (s);
}

void	list_split_addback(t_line **lst, char *arg)
{
	int		i;
	char	**split_token;

	i = 0;
	split_token = ft_token_split(arg);
	while (split_token[i])
	{
		ft_listadd_back(lst, ft_listnew(ft_strdup(split_token[i])));
		i++;
	}
	free_split(split_token);
}

char	**ft_token_split(char *arg)
{
	char	*s;
	char	**split_token;
	int		split_num;
	int		i;

	s = (char *)arg;
	split_num = is_token_quote(arg);
	split_token = (char **)malloc(sizeof(char *) * (split_num + 1));
	split_token[split_num] = NULL;
	i = -1;
	while (++i < split_num)
	{
		if (is_token(s) == 1)
			s = put_token_byte(split_token, s, i, *s);
		else if (is_token(s) == 2)
			s = put_token_bytes(split_token, s, i);
		else
			s = put_bytes(split_token, s, i);
	}
	return (split_token);
}

char	*put_token_bytes(char **split_token, char *s, int i)
{
	split_token[i] = (char *)malloc(sizeof(char) * (3));
	split_token[i][0] = '>';
	split_token[i][1] = '>';
	split_token[i][2] = '\0';
	s = s + 2;
	return (s);
}

char	*put_token_byte(char **split_token, char *s, int i, char c)
{
	split_token[i] = (char *)malloc(sizeof(char) * (2));
	split_token[i][0] = c;
	split_token[i][1] = '\0';
	s++;
	return (s);
}
