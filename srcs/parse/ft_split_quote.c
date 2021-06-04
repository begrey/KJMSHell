/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:51:42 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 10:13:03 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		flag_check(const char c, char flag)
{
	if (!flag)
	{
		if (is_quote(c))
		{
			if (c == '\'')
				flag = '\'';
			else
				flag = '\"';
		}
	}
	else
	{
		if (c == flag)
			flag = '\0';
	}
	return (flag);
}

static int	get_word_num(const char *str)
{
	char	**split;
	char	*s;
	char	flag;
	int		word_num;
	int		split_point;

	split = NULL;
	s = (char *)str;
	while (is_space(*s))
		s++;
	if (!(*s))
		return (0);
	word_num = 1;
	flag = '\0';
	split_point = 0;
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
			if_not_flag_quote(&s, &word_num);
		if (split_point != word_num)
			split_point = word_num;
		s++;
	}
	return (word_num);
}

int			*get_word_len(const char *str, char flag, int word_num)
{
	char	*s;
	int		len;
	int		*word_len;
	int		*word_len2;

	word_len = NULL;
	word_len = (int *)malloc(sizeof(int) * get_word_num(str));
	word_len2 = word_len;
	s = (char *)str;
	len = 0;
	while (is_space(*s))
		s++;
	if (!(*s))
		return (NULL);
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag && is_space(*s))
			is_space_len(&s, &word_num, &word_len2, &len);
		s++;
		len++;
	}
	if (len)
		*word_len2 = len;
	return (word_len);
}

char		put_split_quote(char *s, int *word_num, int *len, char ***split)
{
	char	flag;

	flag = '\0';
	while (*(s))
	{
		flag = flag_check(*(s), flag);
		if (!flag && is_space(*(s)))
			check_space_word_num(&(s), &(*word_num), &(*len));
		(*split)[(*word_num) - 1][(*len)] = *(s);
		(s)++;
		(*len)++;
	}
	return (flag);
}

char		**ft_split_quote(char *s, char **split, char flag)
{
	int		word_num;
	int		word_num2;
	int		len;
	int		*word_len;
	int		i;

	if (s[0] == '\0')
		return (return_if_null(split));
	split = NULL;
	word_num2 = get_word_num(s);
	word_len = get_word_len(s, flag, 1);
	split_malloc(&split, word_num2);
	i = -1;
	while (++i < word_num2)
		split_i_malloc(split, word_len, i);
	if ((check_word_num_return(s, &word_num)) == 0)
		return (NULL);
	len = 0;
	flag = put_split_quote(s, &word_num, &len, &split);
	if (flag)
		return (return_if_flag(word_len, split, s));
	free(word_len);
	return (split);
}
