/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:10:01 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 13:04:00 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_token(char *s)
{
	if (*s == ';' || *s == '|' || (*s == '>' && *(s + 1) != '>') || *s == '<')
		return (1);
	else if (*s == '>' && *(s + 1) == '>')
		return (2);
	return (0);
}

int		is_token_quote(const char *str)
{
	char		*s;
	char		flag;
	int			ret;

	ret = 0;
	flag = 0;
	s = (char *)str;
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (is_token(s) == 1)
				ret++;
			else if (is_token(s) == 2)
			{
				ret++;
				s++;
			}
			if (is_token(s) && !is_token(s + 1) && *(s + 1))
				ret++;
		}
		s++;
	}
	return (ret);
}

int		where_token(char *str)
{
	char		*s;
	char		flag;
	int			ret;
	int			i;

	i = 0;
	s = (char *)str;
	ret = 0;
	flag = 0;
	while (s[i])
	{
		flag = flag_check(s[i], flag);
		if (!flag)
		{
			if (is_token(&(s[i])))
				return (i);
		}
		i++;
	}
	return (i);
}

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

char	*put_token_byte(char **split_token, char *s, int i, char c)
{
	split_token[i] = (char *)malloc(sizeof(char) * (2));
	split_token[i][0] = c;
	split_token[i][1] = '\0';
	s++;
	return (s);
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

int		check_single_escape(const char *s)
{
	char *temp;

	temp = (char *)s;
	while (*temp)
	{
		if (*temp == '\\')
		{
			temp++;
			if (*temp == '\0')
				return (-1);
		}
		temp++;
	}
	return (0);
}

int		ft_strerror(char *s)
{
	char *temp;

	temp = s;
	printf("%s", temp);
	return (-1);
}

void	convert_split(char **split_line, t_env *env)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_line[i])
	{
		temp = split_line[i];
		split_line[i] = convert_env(split_line[i], env);
		free(temp);
		i++;
	}
}

void	trim_split(char **split_line)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_line[i])
	{
		temp = split_line[i];
		split_line[i] = ft_strtrim(split_line[i], " ");
		free(temp);
		i++;
	}
}

void	addback_split(char **split_line, t_line **line)
{
	int		i;

	i = 0;
	while (split_line[i])
	{
		if ((is_token_quote(split_line[i])))
			list_split_addback(line, split_line[i]);
		else
			ft_listadd_back(line, ft_listnew(ft_strdup(split_line[i])));
		i++;
	}
}

int		make_list(t_env *env)
{
	t_line	*line;
	char	**split_line;
	char	*escape_line;
	char	*s_line;
	char	**split;

	split = NULL;
	line = NULL;
	s_line = ft_strdup(g_line);
	escape_line = convert_escape(s_line);
	free(s_line);
	escape_line[ft_strlen(escape_line) - 1] = '\0';
	if (check_single_escape(escape_line) == -1
			|| !(split_line = ft_split_quote(escape_line, split, '\0')))
		return (ft_strerror("syntax error\n"));
	free(escape_line);
	trim_split(split_line);
	convert_split(split_line, env);
	addback_split(split_line, &line);
	if ((redir_syn_check(line)) == -1 || (token_syn_check(line)) == -1)
		return (-1);
	split_by_semi(line, env);
	free_split(split_line);
	return (0);
}
