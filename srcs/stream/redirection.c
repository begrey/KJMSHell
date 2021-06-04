/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:04:24 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 13:53:53 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		convert_stream(int *fd, int *fd_temp)
{
	if (fd[1] > 0)
	{
		(*fd_temp) = dup(1);
		dup2(fd[1], 1);
	}
}

void		restore_stream(int *fd, int fd_temp)
{
	if (fd[1] > 0)
	{
		dup2(fd_temp, 1);
		close(fd[1]);
	}
}

void		init_re_name(t_line *line, int *re_num,
		int **re_type, char ***re_name)
{
	(*re_num) = redir_num(line);
	(*re_name) = (char **)malloc(sizeof(char *) * ((*re_num) + 1));
	(*re_name)[(*re_num)] = NULL;
	(*re_type) = (int *)malloc(sizeof(int) * ((*re_num)));
}

void		free_redir(char **re_name, int *re_type, int *fd)
{
	free_split(re_name);
	free(re_type);
	free(fd);
}

void		ft_redirection(t_line *line, t_env *env, int pip_flag, int *fd)
{
	int		re_num;
	char	**re_name;
	int		*re_type;
	int		fd_temp;
	int		j;

	init_re_name(line, &re_num, &re_type, &re_name);
	put_redir(line, &re_name, &re_type, -1);
	line = ft_list_delredir(line);
	delete_escape_list(line);
	del_qoute_list(line);
	restore_escape_list(line);
	if ((j = redirection_open(&fd, re_num, re_type, re_name)) == -2)
	{
		put_return(1, env);
		return ;
	}
	convert_stream(fd, &fd_temp);
	if (j == -1 || line->next)
		exec_command(line, NULL, env, pip_flag);
	else
		exec_command(line, re_name[j], env, pip_flag);
	restore_stream(fd, fd_temp);
	free_redir(re_name, re_type, fd);
}
