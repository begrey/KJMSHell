/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:00:42 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:40:46 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		dup_pipe(t_line *list, int pipefd[2], int flags, t_env *env)
{
	pid_t cpid;

	cpid = fork();
	if (cpid > 0)
		return ;
	else if (cpid < 0)
		perror("fork");
	if (flags & STDIN_PIPE)
		if (dup2(pipefd[READ], STDIN_FILENO) < 0)
			perror("dup2");
	if (flags & STDOUT_PIPE)
		if (dup2(pipefd[WRITE], STDOUT_FILENO) < 0)
			perror("dup2");
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	ft_redirection(list, env, cpid, NULL);
}

void		pipe_struct(t_pipe *pip)
{
	t_pipe	*pip_temp;

	pip_temp = pip;
	while (pip_temp != NULL)
	{
		pipe(pip_temp->fd);
		pip_temp = pip_temp->next;
	}
}

int			pipe_exec(t_pipe *pip, t_line **list, t_env *env)
{
	t_pipe	*pip_temp;
	int		temp_pipefd[2];
	int		i;
	int		status;

	i = 0;
	pipe_struct(pip);
	pip_temp = pip;
	dup_pipe(list[i++], pip_temp->fd, STDOUT_PIPE, env);
	close(pip_temp->fd[WRITE]);
	while (pip_temp->next != NULL)
	{
		temp_pipefd[0] = pip_temp->fd[READ];
		temp_pipefd[1] = pip_temp->next->fd[WRITE];
		dup_pipe(list[i++], temp_pipefd, STDIN_PIPE | STDOUT_PIPE, env);
		close(pip_temp->fd[READ]);
		pip_temp = pip_temp->next;
		close(pip_temp->fd[WRITE]);
	}
	dup_pipe(list[i], pip_temp->fd, STDIN_PIPE, env);
	while (wait(&status) > 0)
		;
	free_pipe(pip);
	return (status);
}

t_line		**set_pipe_arglist(t_line *list, int pip)
{
	t_line	*temp;
	t_line	*iter;
	t_line	**arg_list;
	int		i;
	int		index;

	index = 0;
	temp = list;
	iter = list;
	arg_list = (t_line **)malloc(sizeof(t_line *) * (pip + 2));
	while (temp != NULL)
	{
		i = ft_split_list_token(temp, '|');
		temp = ft_list_null_term(temp, i);
		arg_list[index] = iter;
		index++;
		iter = temp;
	}
	arg_list[index] = NULL;
	return (arg_list);
}

void		split_by_pipe(t_line *list, t_env *env)
{
	t_pipe	*pipe;
	t_line	**arg_list;
	int		pip;
	int		i;

	pipe = NULL;
	pip = 0;
	i = 0;
	pip = ft_pipesize(list);
	i = pip;
	arg_list = set_pipe_arglist(list, pip);
	while (i != 0)
	{
		ft_pipeadd_back(&pipe, ft_pipenew());
		i--;
	}
	if (pip == 0)
		ft_redirection(list, env, 1, NULL);
	else
	{
		i = pipe_exec(pipe, arg_list, env);
		put_return(i / 256, env);
	}
	free_list_struct(arg_list);
}
