/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:04:24 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/02 22:19:46 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

void		put_left_or_right(t_line **temp, int *type)
{
	if ((*temp)->arg[0] == '<')
	{
		(*type) = 3;
		(*temp) = (*temp)->next;
	}
	else
	{
		(*type) = 1;
		if ((*temp)->arg[1] == '>')
			(*type) = 2;
		(*temp) = (*temp)->next;
	}
}

void		put_redir(t_line *temp, char ***re_name, int **re_type)
{
	int		flag;
	int		type;
	int		i;

	i = -1;
	while (temp)
	{
		type = 0;
		if (is_redir(temp->arg[0]))
		{
			put_left_or_right(&temp, &type);
			flag = 0;
			while (temp && !is_redir(temp->arg[0]))
			{
				if (flag == 0)
				{
					(*re_type)[++i] = type;
					(*re_name)[i] = ft_strdup(temp->arg);
				}
				temp = temp->next;
				flag++;
			}
		}
		if (temp && !is_redir(temp->arg[0]))
			temp = temp->next;
	}
}

int			redir_num(t_line *line)
{
	int		num;
	t_line	*temp;

	num = 0;
	temp = line;
	while (temp)
	{
		if (is_redir(temp->arg[0]))
		{
			temp = temp->next;
			if (is_redir(temp->arg[0]))
				temp = temp->next;
			while (temp && !is_redir(temp->arg[0]))
				temp = temp->next;
			num++;
		}
		if (temp && !is_redir(temp->arg[0]))
			temp = temp->next;
	}
	return (num);
}

t_line		*ft_list_delredir(t_line *line)
{
	t_line	*temp;
	t_line	*redir;
	t_line	*file;

	if (!line)
	{
		line = ft_listnew(ft_strdup(""));
		return (line);
	}
	temp = line;
	while (line && which_redir((line)->arg))
	{
		redir = line;
		file = line->next;
		(line) = (line)->next->next;
//		free_struct(redir);
//		free_struct(file);
		if (line != NULL)
			(line)->prev = NULL;
	}
	temp = line;
	while (temp)
	{
		if (which_redir(temp->arg))
		{
			redir = temp;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		//	free_struct(redir);
			temp = temp->next;
			if (temp && temp->prev)
			{
				file = temp;
				temp->prev->next = temp->next;
				if (temp->next)
					temp->next->prev = temp->prev;
		//		free_struct(file);
			}
		}
		temp = temp->next;
	}
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

void		delete_escape_list(t_line *line)
{
	t_line	*temp;
	char	*str;

	temp = line;
	while (temp)
	{
		str = temp->arg;
		temp->arg = delete_escape(temp->arg);
		free(str);
		temp = temp->next;
	}
}

void		del_qoute_list(t_line *line)
{
	t_line	*temp;
	char	*str;

	temp = line;
	while (temp)
	{
		str = temp->arg;
		(temp)->arg = ft_del_quote((temp)->arg);
		free(str);
		temp = (temp)->next;
	}
}

void		restore_escape_list(t_line *line)
{
	t_line	*temp;
	char	*str;

	temp = line;
	while (temp)
	{
		str = temp->arg;
		temp->arg = restore_escape(temp->arg);
		free(str);
		temp = temp->next;
	}
}

void		ft_redirection(t_line *line, t_env *env, int pip_flag)
{
	int		re_num;
	char	**re_name;
	int		*re_type;

	int		i;
	t_line	*temp;
	int		fd_wr;
	int		fd_op;
	int		fd_temp;
	int		j;
	char	*input;

	temp = line;
	line = ft_list_delredir(temp);
	delete_escape_list(line);
	del_qoute_list(line);
	restore_escape_list(line);

	re_num = redir_num(temp);
	re_name = (char **)malloc(sizeof(char *) * (re_num + 1));
	re_name[re_num] = NULL;
	re_type = (int *)malloc(sizeof(int) * (re_num));
	put_redir(temp, &re_name, &re_type);
	fd_wr = -1;
	j = -1;
	i = 0;
	while (i < re_num)
	{
		if (re_type[i] == 1)
		{
			fd_wr = open(re_name[i], O_RDWR | O_CREAT | O_TRUNC, 00777);
		}
		else if (re_type[i] == 2)
		{
			fd_wr = open(re_name[i], O_RDWR | O_APPEND | O_CREAT, 00777);
		}
		else if (re_type[i] == 3)
		{
			j = i;
			if ((fd_op = open(re_name[i], O_RDONLY, 00777)) < 0)
			{
				printf("%s\n", strerror(errno));
				put_return(1, env);
				return ;
			}
		}
		i++;
	}
	temp = line;
	if (j == -1 || temp->next)
	{
		j = 0;
		input = NULL;
	}
	else
		input = re_name[j];
	temp = line;
	if (fd_wr > 0)
	{
		fd_temp = dup(1);
		dup2(fd_wr, 1);
	}
	exec_command(temp, input, env, pip_flag);
	if (fd_wr > 0)
	{
		dup2(fd_temp, 1);
		close(fd_wr);
	}
	free_split(re_name);
	free(re_type);
}
