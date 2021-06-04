/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:11:26 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 15:26:19 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		list_last_del(t_line *temp, t_line *redir,
		t_line *file, t_line *line)
{
	temp = line;
	while (temp)
	{
		if (which_redir(temp->arg))
		{
			redir = temp;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp = temp->next;
			free(redir->arg);
			free(redir);
			if (temp && temp->prev)
			{
				file = temp;
				temp->prev->next = temp->next;
				if (temp->next)
					temp->next->prev = temp->prev;
				temp = temp->next;
				free(file->arg);
				free(file);
			}
		}
		else
			temp = temp->next;
	}
}

void		list_first_del(t_line **redir, t_line **line, t_line **file)
{
	while ((*line) && which_redir(((*line))->arg))
	{
		(*redir) = (*line);
		(*file) = (*line)->next;
		(*line) = (*line)->next->next;
		if ((*line) != NULL)
			((*line))->prev = NULL;
	}
}

t_line		*ft_list_delredir(t_line *line)
{
	t_line	*temp;
	t_line	*redir;
	t_line	*file;

	redir = NULL;
	file = NULL;
	if (!line)
	{
		line = ft_listnew(ft_strdup(""));
		return (line);
	}
	temp = line;
	list_first_del(&redir, &line, &file);
	list_last_del(temp, redir, file, line);
	return (line);
}

int			check_num_delquote(char *str)
{
	int		num;
	char	*s;
	int		flag;
	int		compare;

	flag = 0;
	num = 0;
	s = (char *)str;
	while (*s)
	{
		compare = flag;
		flag = flag_check(*s, flag);
		num++;
		if (flag != compare)
			num--;
		s++;
	}
	return (num);
}

char		*ft_del_quote(char *str)
{
	char	*temp;
	char	flag;
	char	*s;
	int		i;
	char	compare;

	i = check_num_delquote(str);
	temp = (char *)malloc(sizeof(char) * (i + 1));
	temp[i] = '\0';
	s = (char *)str;
	flag = 0;
	i = -1;
	while (*s)
	{
		compare = flag;
		flag = flag_check(*s, flag);
		if (compare != flag)
			s++;
		else
		{
			temp[++i] = *s;
			s++;
		}
	}
	return (temp);
}
