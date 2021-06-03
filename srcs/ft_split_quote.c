/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:51:42 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 08:53:05 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			is_space(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int			is_quote(const char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

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

int			*get_word_len(const char *str, char flag)
{
	char	*s;
	int		word_num;
	int		len;
	int		*word_len;
	int		*word_len2;

	word_len = (int *)malloc(sizeof(int) * get_word_num(str));
	word_len2 = word_len;
	s = (char *)str;
	len = 0;
	while (is_space(*s))
		s++;
	if (!(*s))
		return (NULL);
	word_num = 1;
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (is_space(*s))
				is_space_len(&s, &word_num, &word_len2, &len);
		}
		s++;
		len++;
	}
	if (len)
		*word_len2 = len;
	return (word_len);
}

char		**return_if_null(char **split)
{
	split = (char **)malloc(sizeof(char *) * (2));
	split[1] = NULL;
	split[0] = ft_strdup("");
	return (split);
}

char		**ft_split_quote(const char *str)
{
	char	**split;
	char	*s;
	char	flag;
	int		word_num;
	int		word_num2;
	int		len;
	int		split_point;
	int		*word_len;
	int		i;

	flag = '\0';
	split = NULL;
	if (str[0] == '\0')
		return (return_if_null(split));
	split = NULL;
	word_num2 = get_word_num(str);
	word_len = get_word_len(str, flag);
	split = (char **)malloc(sizeof(char *) * (word_num2 + 1));
	split[word_num2] = NULL;
	i = -1;
	while (++i < word_num2)
	{
		split[i] = (char *)malloc(sizeof(char) * (word_len[i] + 1));
		split[i][word_len[i]] = '\0';
	}
	s = (char *)str;
	while (is_space(*s))
		s++;
	if (*s)
		word_num = 1;
	else
	{
		word_num = 0;
		return (NULL);
	}
	len = 0;
	split_point = 0;
	while (*s)
	{
		if (split_point != word_num)
		{
			split_point = word_num;
		}
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (is_space(*s))
			{
				while (is_space(*s))
					s++;
				if (*s)
				{
					word_num++;
					len = 0;
					s--;
				}
			}
		}
		split[word_num - 1][len] = *s;
		s++;
		len++;
	}
	if (flag)
	{
		free(word_len);
		free_split(split);
		return (0);
	}
	free(word_len);
	return (split);
}
