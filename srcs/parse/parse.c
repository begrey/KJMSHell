/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:10:01 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 10:11:25 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_single_escape(char *s)
{
	char *temp;

	temp = (char *)s;
	while (*temp)
	{
		if (*temp == '\\')
		{
			temp++;
			if (*temp == '\0')
			{
				free(s);
				return (-1);
			}
		}
		temp++;
	}
	return (0);
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

	init_make_list(&split, &line);
	g_line[ft_strlen(g_line) - 1] = '\0';
	s_line = ft_strdup(g_line);
	escape_line = convert_escape(s_line);
	free(s_line);
	if (check_single_escape(escape_line) == -1
			|| !(split_line = ft_split_quote(escape_line, split, '\0')))
		return (ft_strerror("syntax error\n"));
	free(escape_line);
	trim_split(split_line);
	convert_split(split_line, env);
	addback_split(split_line, &line);
	if ((redir_syn_check(line, split_line)) == -1 ||
			(token_syn_check(line, split_line)) == -1)
		return (-1);
	split_by_semi(line, env);
	free_split(split_line);
	return (0);
}
